#include"linklist.h";
using namespace std;
typedef struct Student
{
	Linklistnode head;
	int age;
	char name[33];
}Student;
int main()
{
	Student s1, s2, s3, s4, s5, s6, s7, s8;
	Linklistv * list = NULL;
	list = Linklist_Create();
	if (list == NULL)
	{
		cout << "error create list" << endl;
		return -1;
	}
	s1.age = 1;
	s2.age = 2;
	s3.age = 3;
	s4.age = 4;
	s5.age = 5;
	s6.age = 6;
	s7.age = 7;
	s8.age = 8;
	int len = 2;
	len = Linklist_Length(list);
	cout << "输出现在链表的长度";
	cout << len << endl;
	Linklist_Insert(list, (Linklistnode *)&s1, 0);
	Linklist_Insert(list, (Linklistnode *)&s2, 0);
	Linklist_Insert(list, (Linklistnode *)&s3, 0); 
	Linklist_Insert(list, (Linklistnode *)&s4, 0);
	Linklist_Insert(list, (Linklistnode *)&s5, 0);
	Linklist_Insert(list, (Linklistnode *)&s6, 0);
	Linklist_Insert(list, (Linklistnode *)&s7, 0);
	Linklist_Insert(list, (Linklistnode *)&s8, 0);
	cout << "shuchulianbiao" << endl;
	for (int i = 0; i < Linklist_Length(list); i++)
	{
		Student * temp = (Student *)Linklist_Get(list, i);
		cout << temp->age << endl;
	}
	cout << "输出完毕;删除第二项" << endl;
	Linklist_Delete(list,2);
	cout << "zai cai shu chu :" << endl;
	for (int i = 0; i < Linklist_Length(list); i++)
	{
		Student * temp = (Student *)Linklist_Get(list, i);
		cout << temp->age << endl;
	}
	cout << "清空链表" << endl;
	Linklist_Clear(list);
	len = Linklist_Length(list);
	cout << "输出现在的长度";
	cout << len << endl;
	Linklist_Destory(list);
	system("pause");
	return 0;
}