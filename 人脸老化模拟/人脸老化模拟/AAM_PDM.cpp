/****************************************************************************
*
* Copyright (c) 2008 by Yao Wei, all rights reserved.
*
* Author:      	Yao Wei
* Contact:     	njustyw@gmail.com
*
* This software is partly based on the following open source:
*
*		- OpenCV
*
****************************************************************************/

#include "AAM_PDM.h"
using namespace std;

//int aligni = 0;

AAM_PDM::AAM_PDM()
{
    __MeanShape = 0;
    __ShapesEigenVectors = 0;
    __ShapesEigenValues = 0;
    __matshape = 0;
}

AAM_PDM::~AAM_PDM()
{
    cvReleaseMat(&__MeanShape);
    cvReleaseMat(&__ShapesEigenVectors);
    cvReleaseMat(&__ShapesEigenValues);
    cvReleaseMat(&__matshape);
}

void AAM_PDM::Train(const std::vector<AAM_Shape> &AllShapes, double percentage /* = 0.95 */)
{
    printf("################################################\n");
    printf("Build Point Distribution Model...\n");

    int nSamples = AllShapes.size();
    int nPoints = AllShapes[0].NPoints();
    __matshape = cvCreateMat(1, nPoints*2, CV_64FC1);

    std::vector<AAM_Shape> AlignedShapes = AllShapes;
    AAM_PDM::AlignShapes(AlignedShapes);

    /*string s;
    char c[10];
    itoa(aligni,c,10);
    std::ofstream alignp;
    alignp.open("pts_"+ std::string(c) +".txt");
    aligni++;*/

    // Assign all points positions from vector<AAM_Shape> to CvMat
    CvMat *m_CVShapes = cvCreateMat (nSamples, nPoints * 2, CV_64FC1);
    for(int i = 0; i < nSamples; i++)
    {
        for(int j = 0; j < nPoints; j++)
        {
            CV_MAT_ELEM(*m_CVShapes, double, i, 2*j  ) = AlignedShapes[i][j].x;
            CV_MAT_ELEM(*m_CVShapes, double, i, 2*j+1) = AlignedShapes[i][j].y;
            //alignp << AlignedShapes[i][j].x << " " << AlignedShapes[i][j].y << " ";
        }
        //alignp << std::endl;
    }

    //alignp.close();

    DoPCA(m_CVShapes, percentage);
    __AAMRefShape.Mat2Point(__MeanShape);

    // this step is not necessary!
    __AAMRefShape.Translate(-__AAMRefShape.MinX(), -__AAMRefShape.MinY());

    cvReleaseMat(&m_CVShapes);
    printf("################################################\n\n");
}

void AAM_PDM::Train(const std::vector<AAM_Shape> &AllShapes, std::vector<AAM_Shape> &AlignedShapes, double percentage/* =0.95 */)
{
    printf("################################################\n");
    printf("Build Point Distribution Model...\n");

    int nSamples = AllShapes.size();
    int nPoints = AllShapes[0].NPoints();
    __matshape = cvCreateMat(1, nPoints*2, CV_64FC1);

    AlignedShapes = AllShapes;
    AAM_PDM::AlignShapes(AlignedShapes);

    // Assign all points positions from vector<AAM_Shape> to CvMat
    CvMat *m_CVShapes = cvCreateMat (nSamples, nPoints * 2, CV_64FC1);
    for(int i = 0; i < nSamples; i++)
    {
        for(int j = 0; j < nPoints; j++)
        {
            CV_MAT_ELEM(*m_CVShapes, double, i, 2*j  ) = AlignedShapes[i][j].x;
            CV_MAT_ELEM(*m_CVShapes, double, i, 2*j+1) = AlignedShapes[i][j].y;
        }
    }

    DoPCA(m_CVShapes, percentage);
    __AAMRefShape.Mat2Point(__MeanShape);

    // this step is not necessary!
    __AAMRefShape.Translate(-__AAMRefShape.MinX(), -__AAMRefShape.MinY());

    cvReleaseMat(&m_CVShapes);
    printf("################################################\n\n");
}

void AAM_PDM::AlignShapes(std::vector<AAM_Shape> &AllShapes)
{
    printf("Align all shapes...\n");

    int nSamples = AllShapes.size();
    int nPoints = AllShapes[0].NPoints();

    for(int ii=0; ii < nSamples; ii++)	AllShapes[ii].Centralize();

    // calculate the mean shape
    AAM_Shape meanShape;
    AAM_PDM::CalcMeanShape(meanShape, AllShapes);

    /*************************************************************************************************************/
    double thisfacewidth = meanShape.GetWidth();
    if(stdwidth < thisfacewidth) meanShape.Scale(stdwidth / thisfacewidth);

    // We choose an initial estimate AlignedShapes[0]
    AAM_Shape refShape(meanShape);
    const AAM_Shape ConstRefShape(meanShape);
    AAM_Shape NewMeanShape(meanShape);

    // do a number of alignment iterations until the mean shape estimate is stable
    double diff, diff_max = 0.001;
    const int max_iter = 30;
    for(int iter = 0; iter < max_iter; iter++)
    {
        //align all shapes to the mean shape estimate
        for(int i = 0; i < nSamples; i++)
        {
            // align the i-th shape to the estimate of the mean shape
            AllShapes[i].AlignTo(refShape);
        }

        // Re-estimate new mean shape from aligned shapes
        AAM_PDM::CalcMeanShape(NewMeanShape, AllShapes);

        // Constrain new mean shape by aligning it to ref shape
        NewMeanShape.AlignTo(ConstRefShape);

        diff = (NewMeanShape-refShape).GetNorm2();

        printf("Alignment iteration #%i, mean shape est. diff. = %g\n", iter, diff );

        if(diff <= diff_max) break; //converged

        //if not converged, come on iterations
        refShape = NewMeanShape;
    }

    AAM_PDM::CalcMeanShape(meanShape, AllShapes);
}

void AAM_PDM::CalcMeanShape(AAM_Shape &MeanShape, const std::vector<AAM_Shape> &AllShapes)
{
    MeanShape.resize(AllShapes[0].NPoints());
    MeanShape = 0;
    for(int i = 0; i < AllShapes.size(); i++)     MeanShape += AllShapes[i];
    MeanShape /= AllShapes.size();
}

void AAM_PDM::DoPCA(const CvMat* m_CVShapes, double percentage)
{
    printf("Doing PCA of shapes datas...");

    int nSamples = m_CVShapes->rows;
    int nPointsby2 = m_CVShapes->cols;
    int nEigenAtMost = MIN(nSamples, nPointsby2);

    CvMat* tmpEigenValues = cvCreateMat(1, nEigenAtMost, CV_64FC1);
    CvMat* tmpEigenVectors = cvCreateMat(nEigenAtMost, nPointsby2, CV_64FC1);
    __MeanShape = cvCreateMat(1, nPointsby2, CV_64FC1 );

    cvCalcPCA(m_CVShapes, __MeanShape,
              tmpEigenValues, tmpEigenVectors, CV_PCA_DATA_AS_ROW);

    double allSum = cvSum(tmpEigenValues).val[0];
    double partSum = 0.0;
    int nTruncated = 0;
    double largesteigval = cvmGet(tmpEigenValues, 0, 0);
    for(int i = 0; i < nEigenAtMost; i++)
    {
        double thiseigval = cvmGet(tmpEigenValues, 0, i);
        if(thiseigval / largesteigval < 0.0001) break; // firstly check
        partSum += thiseigval;
        ++ nTruncated;
        if(partSum/allSum >= percentage)	break;    //secondly check
    }

    __ShapesEigenValues = cvCreateMat(1, nTruncated, CV_64FC1);
    __ShapesEigenVectors = cvCreateMat(nTruncated, nPointsby2, CV_64FC1);

    CvMat G;
    cvGetCols(tmpEigenValues, &G, 0, nTruncated);
    cvCopy(&G, __ShapesEigenValues);

    cvGetRows(tmpEigenVectors, &G, 0, nTruncated);
    cvCopy(&G, __ShapesEigenVectors);

    cvReleaseMat(&tmpEigenVectors);
    cvReleaseMat(&tmpEigenValues);
    printf("Done (%d/%d)\n", nTruncated, nEigenAtMost);
}

void AAM_PDM::CalcLocalShape(const CvMat* p, CvMat* s)
{
    cvBackProjectPCA(p, __MeanShape, __ShapesEigenVectors,	s);
}

void AAM_PDM::CalcGlobalShape(const CvMat* q, CvMat* s)
{
    int npoints = nPoints();
    double* fasts = s->data.db;
    double a=cvmGet(q,0,0)+1, b=cvmGet(q,0,1),
           tx=cvmGet(q,0,2), ty=cvmGet(q,0,3);
    double x, y;
    for(int i = 0; i < npoints; i++)
    {
        x = fasts[2*i  ];
        y = fasts[2*i+1];

        fasts[2*i  ] = a*x-b*y+tx;
        fasts[2*i+1] = b*x+a*y+ty;
    }
}

void AAM_PDM::CalcShape(const CvMat* p, const CvMat* q, CvMat* s)
{
    CalcLocalShape(p, s);
    CalcGlobalShape(q, s);
}

void AAM_PDM::CalcShape(const CvMat* pq, CvMat* s)
{
    int nmodes = nModes(), npoints = nPoints();
//	assert(pq->cols == 4+nmodes && s->cols == npoints*2);

    CvMat p;
    cvGetCols(pq, &p, 4, 4+nmodes);
    cvBackProjectPCA(&p, __MeanShape, __ShapesEigenVectors,	s);

    double* fasts = s->data.db;
    double a=cvmGet(pq,0,0)+1, b=cvmGet(pq,0,1),
           tx=cvmGet(pq,0,2), ty=cvmGet(pq,0,3);
    double x, y;
    for(int i = 0; i < npoints; i++)
    {
        x = fasts[2*i  ];
        y = fasts[2*i+1];

        fasts[2*i  ] = a*x-b*y+tx;
        fasts[2*i+1] = b*x+a*y+ty;
    }
}

void AAM_PDM::CalcShape(const CvMat* pq, AAM_Shape& shape)
{
    CalcShape(pq, __matshape);
    shape.Mat2Point(__matshape);
}

void AAM_PDM::CalcParams(const CvMat* s, CvMat* pq)
{
    __x.Mat2Point(s);

    CalcParams(__x, pq);
}

void AAM_PDM::CalcParams(const CvMat* s, CvMat* p, CvMat* q)
{
    int nmodes = nModes(), npoints = nPoints();
//	assert(pq->cols == 4+nmodes);

    double a, b, tx, ty;
    double a_, b_, tx_, ty_;
    double norm;

    __y.Mat2Point(s);
    __y.COG(tx, ty);
    __y.Translate(-tx, -ty);
    cvmSet(q,0,2,tx);
    cvmSet(q,0,3,ty);

    // do a few iterations to get (s, theta, p)
    cvZero(p);
    for(int iter = 0; iter < 2; iter++)
    {
        cvBackProjectPCA(p, __MeanShape, __ShapesEigenVectors,	__matshape);
        __x.Mat2Point(__matshape);

        __x.AlignTransformation(__y, a, b, tx, ty); //in fact, tx = ty = 0

        norm = a*a + b*b;
        a_ = a / norm;
        b_ = -b / norm;
        tx_ = (-a*tx - b*ty) / norm;
        ty_ = (b*tx - a*ty) / norm;
        __x = __y;
        __x.TransformPose(a_, b_, tx_, ty_);

        __x.Point2Mat(__matshape);
        cvProjectPCA(__matshape, __MeanShape, __ShapesEigenVectors, p);
    }

    cvmSet(q, 0, 0, a -1);
    cvmSet(q, 0, 1, b);
    Clamp(p, 1.8);
}

void AAM_PDM::CalcParams(const AAM_Shape& shape, CvMat* pq)
{
    int nmodes = nModes(), npoints = nPoints();
//	assert(pq->cols == 4+nmodes);

    double a, b, tx, ty;
    double a_, b_, tx_, ty_;
    double norm;

    __y = shape;
    __y.COG(tx, ty);
    __y.Translate(-tx, -ty);
    cvmSet(pq,0,2,tx);
    cvmSet(pq,0,3,ty);

    // do a few iterations to get (s, theta, p)
    CvMat p;
    cvGetCols(pq, &p, 4, 4+nmodes);
    cvZero(&p);
    for(int iter = 0; iter < 2; iter++)
    {
        cvBackProjectPCA(&p, __MeanShape, __ShapesEigenVectors,	__matshape);
        __x.Mat2Point(__matshape);

        __x.AlignTransformation(__y, a, b, tx, ty); //in fact, tx = ty = 0

        norm = a*a + b*b;
        a_ = a / norm;
        b_ = -b / norm;
        tx_ = (-a*tx - b*ty) / norm;
        ty_ = (b*tx - a*ty) / norm;
        __x = __y;
        __x.TransformPose(a_, b_, tx_, ty_);

        __x.Point2Mat(__matshape);
        cvProjectPCA(__matshape, __MeanShape, __ShapesEigenVectors, &p);
    }

    cvmSet(pq, 0, 0, a -1);
    cvmSet(pq, 0, 1, b);
    Clamp(&p, 1.8);
}

void AAM_PDM::Clamp(CvMat* p, double s_d /* = 3.0 */)
{
    double* fastp = p->data.db;
    double* fastv = __ShapesEigenValues->data.db;
    int nmodes = nModes();
    double limit;

    for(int i = 0; i < nmodes; i++)
    {
        limit = s_d*sqrt(fastv[i]);
        if(fastp[i] > limit) fastp[i] = limit;
        else if(fastp[i] < -limit) fastp[i] = -limit;
    }
}

void AAM_PDM::Write(std::ofstream& os)
{
    os << nPoints() << " " << nModes() << std::endl;
    os << __MeanShape << std::endl;
    os << __ShapesEigenValues << std::endl;
    os << __ShapesEigenVectors << std::endl;
    __AAMRefShape.Write(os);
    os << std::endl;
}

void AAM_PDM::Read(std::ifstream& is)
{
    int _nPoints, _nModes;
    is >> _nPoints >> _nModes;

    __MeanShape = cvCreateMat(1, _nPoints*2, CV_64FC1);
    __ShapesEigenValues = cvCreateMat(1, _nModes, CV_64FC1);
    __ShapesEigenVectors = cvCreateMat(_nModes, _nPoints*2, CV_64FC1);
    __AAMRefShape.resize(_nPoints);

    is >> __MeanShape;
    is >> __ShapesEigenValues;
    is >> __ShapesEigenVectors;
    __AAMRefShape.Read(is);

    __matshape  = cvCreateMat(1, nPoints()*2, CV_64FC1);
}
