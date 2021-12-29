#include<iostream>
#include<set>
#include<map>
#include<vector>
#include<fstream>
#include<ctime>
using namespace std;


typedef struct Book {
	int record_num;  //记录号
	int book_id;     //书号
	string book_name;    //书名
	int b_ptr;      //书名指针
	string author;  //作者
	int w_ptr;  //作者指针
	string press;   //出版社
	int p_ptr;  //出版社指针 
	int classfity;  //分类
	int collect;    //藏书量
	int borrow;     //借出数
}Book;

typedef struct Index {
	int lhead;  //链头指针
	int length;  //长度
}Index;

typedef struct Reader {
	int reader_num;    //读者号
	string name;        //读者名
	int bn1;            //可借书数
	int bn2;            //已借书数
}Reader;

typedef struct Bbook {
	int reader_num;    //读者号
	int book_id;       //书号
	string borrow_date;   //借书日期
	string return_date;   //还书日期
}Bbook;

map<int, int> bookid_index;
vector<Book> book; 
map<string, Index> name_index;
map<string, Index>author_index;
map<string, Index> press_index;
vector<Reader> reader;
vector<Bbook> bbook;

//读文件
void readfile(string s1, string s2, string s3, string s4);

//书号查询
void find_id(map<int, int> index, int bnum);

//书名查询
void find_name(map<string, Index> index, string name);

//作者查询
void find_author(map<string, Index> index, string author);

//出版社查询
void find_press(map<string, Index> index, string press);

//查找图书
void find_book();

//添加图书
void add();

//展示当前查询图书
void show_book(int index);

//主菜单
int mainmenu();

//删除图书
void Delete();

//输出文件
void outfile();

//借书算法
void borrow_book();

//还书算法
void return_book();

//增加新读者
void add_reader();

//删除读者
void delete_reader();

//输出读者文件
void outreaderfile();

//输出借还文件
void outBRfile();

int main()
{
	int k = 1;
	int n;
	while (k == 1) {
		n = mainmenu();
		switch (n)
		{
		case 1:
			readfile("book_message.txt", "book_index.txt", "author_index.txt", "press_index.txt");
			break;
		case 2:find_book();
			break;
		case 3:add();
			break;
		case 0:
			k = 0;
			cout << "系统退出" << endl;
			outfile();
			break;
		}
	}

}


//读文件
void readfile(string s1, string s2, string s3, string s4) {
	ifstream f1(s1);
	ifstream f2(s2);
	ifstream f3(s3);
	ifstream f4(s4);
	cout << "写入文件中..." << endl;
	while (!f1.eof()) {
		Book temp;
		f1 >> temp.record_num;
		f1 >> temp.book_id;
		f1 >> temp.book_name;
		f1 >> temp.b_ptr;
		f1 >> temp.author;
		f1 >> temp.w_ptr;
		f1 >> temp.press;
		f1 >> temp.p_ptr;
		f1 >> temp.classfity;
		f1 >> temp.collect;
		f1 >> temp.borrow;
		bookid_index.insert(pair<int, int>(temp.book_id, temp.record_num));
		book.push_back(temp);
	}
	while (!f2.eof()) {
		Index temp;
		string temp_s;
		f2 >> temp_s;
		f2 >> temp.lhead;
		f2 >> temp.length;
		name_index.insert(pair<string, Index>(temp_s, temp));
	}
	while (!f3.eof()) {
		Index temp;
		string temp_s;
		f3 >> temp_s;
		f3 >> temp.lhead;
		f3 >> temp.length;
		author_index.insert(pair<string, Index>(temp_s, temp));
	}
	while (!f4.eof()) {
		Index temp;
		string temp_s;
		f4 >> temp_s;
		f4 >> temp.lhead;
		f4 >> temp.length;
		press_index.insert(pair<string, Index>(temp_s, temp));
	}
	cout << "写入成功!" << endl;
	system("pause");
	system("cls");
}

//展示当前查询图书
void show_book(int index)
{

	cout << book[index - 1].book_id
		<< "\t\t" << book[index - 1].book_name
		<< "\t\t" << book[index - 1].author
		<< "\t\t" << book[index - 1].press
		<< "\t\t" << book[index - 1].classfity
		<< "\t\t" << book[index - 1].collect
		<< "\t\t" << book[index - 1].borrow
		<< endl;
}

//根据书号查询图书
void find_id(map<int, int> index, int bnum)
{
	cout << "书号\t\t书名\t\t作者\t\t出版社\t\t分类\t\t藏书量\t\t借出数" << endl;
	// find 返回迭代器指向当前查找元素的位置否则返回map::end()位置
	auto iter = index.find(bnum);
	if (iter != index.end())
		show_book(iter->second);
	else
		cout << "Do not Find" << endl;

}

//根据书名查询图书
void find_name(map<string, Index> index, string name) {
	cout << "书号\t\t书名\t\t作者\t\t出版社\t\t分类\t\t藏书量\t\t借出数" << endl;
	Index result;
	auto iter = index.find(name);
	if (iter != index.end()) {
		result = iter->second;
		int index = result.lhead;
		for (int i = 0; i < result.length; i++) {
			show_book(index);
			index = book[index - 1].b_ptr;
		}
	}
	else {
		cout << "Do not Find" << endl;
	}
}

//根据作者查询图书
void find_author(map<string, Index> index, string author)
{
	cout << "书号\t\t书名\t\t作者\t\t出版社\t\t分类\t\t藏书量\t\t借出数" << endl;
	Index result;
	auto iter = index.find(author);
	if (iter != index.end()) {
		result = iter->second;
		int index = result.lhead;
		for (int i = 0; i < result.length; i++) {
			show_book(index);
			index = book[index - 1].w_ptr;
		}
	}
	else {
		cout << "Do not Find" << endl;
	}
}

//根据出版社查询图书
void find_press(map<string, Index> index, string press)
{
	cout << "书号\t\t书名\t\t作者\t\t出版社\t\t分类\t\t藏书量\t\t借出数" << endl;
	Index result;
	auto iter = index.find(press);
	if (iter != index.end()) {
		result = iter->second;
		int index = result.lhead;
		for (int i = 0; i < result.length; i++) {
			show_book(index);
			index = book[index - 1].p_ptr;
		}
	}
	else {
		cout << "Do not Find" << endl;
	}
}

//查找图书
void find_book()
{
	int a;
	int bno;
	string bname, bauthor, bpress;

	cout << "1、通过书号查询，2、通过书名查询，3、通过作者查询，4、通过出版社查询" << endl;
	cin >> a;
	if (a >= 1 && a <= 4) {

		switch (a)
		{

		case 1:
			cout << "输入书号：";
			cin >> bno;
			find_id(bookid_index, bno);
			break;
		case 2:
			cout << "输入书名：";
			cin >> bname;
			find_name(name_index, bname);
			break;
		case 3:
			cout << "输入作者：";
			cin >> bauthor;
			find_author(author_index, bauthor);
			break;
		case 4:
			cout << "输入出版社：";
			cin >> bpress;
			find_press(press_index, bpress);
			break;
		default:
			break;
		}
	}
	else
		cout << "输入有误" << endl;

	system("pause");
	system("cls");
}

//添加图书
void add()
{
	srand((unsigned)time(NULL));    // 初始化随机数种子
	int record_num1, book_id1, b_ptr1, w_ptr1, p_ptr1, classify1, collect1;
	int borrow1;
	record_num1 = book[book.size() - 1].record_num + 1;
	string book_name1, author1, press1;
	cout << "请输入书号：";
	cin >> book_id1;
	cout << "请输入存进去的数目：";
	cin >> collect1;
	for (unsigned int j = 0; j < book.size(); j++)
	{
		if (book[j].book_id == book_id1)
		{
			book[j].collect += collect1;
			break;
		}
		if (book[j].book_id != book_id1 && j == book.size() - 1)
		{
			borrow1 = 0;
			cout << "请输入书名：";
			cin >> book_name1;
			for (unsigned int k = 0; k < book.size(); k++)
			{
				if (book[k].book_name == book_name1)
				{
					classify1 = book[k].classfity;
					break;
				}
				if (book[k].book_name != book_name1 && k == book.size() - 1)
				{
					classify1 = rand() % 100 + 1;
					int b = 1;
					while (b == 1)
					{
						for (unsigned int k1 = 0; k1 < book.size(); k1++)
						{
							if (book[k1].classfity == classify1)
							{
								classify1 = rand() % 100 + 1;
								break;
							}
							if (k1 == book.size() - 1)
								b = 0;
						}
					}
				}
			}
			cout << "请输入作者：";
			cin >> author1;
			cout << "请输入出版社：";
			cin >> press1;
			for (int i = book.size() - 1; i >= 0; i--)
			{
				if (book[i].book_name == book_name1)
				{
					b_ptr1 = i + 1;
					break;
				}
				if (book[i].book_name != book_name1 && i == 0)
				{
					b_ptr1 = 0;
				}
			}
			for (int i = book.size() - 1; i >= 0; i--)
			{
				if (book[i].author == author1)
				{
					w_ptr1 = i + 1;
					break;
				}
				if (book[i].author != author1 && i == 0)
				{
					w_ptr1 = 0;
				}
			}
			for (int i = book.size() - 1; i >= 0; i--)
			{
				if (book[i].press == press1)
				{
					p_ptr1 = i + 1;
					break;
				}
				if (book[i].press != press1 && i == 0)
				{
					p_ptr1 = 0;
				}
			}
			Book a;
			a.record_num = record_num1;
			a.book_id = book_id1;
			a.book_name = book_name1;
			a.b_ptr = b_ptr1;
			a.author = author1;
			a.w_ptr = w_ptr1;
			a.press = press1;
			a.p_ptr = p_ptr1;
			a.classfity = classify1;
			a.collect = collect1;
			a.borrow = borrow1;
			book.push_back(a);
			break;
		}
	}
}

//输出文件
void outfile()
{
	ofstream out("book_message.txt");  //初始化一个out对象
	if (!out) {             //是否正常打开
		cout << "error";
	}
	else {
		for (unsigned int i = 0; i < book.size(); i++)
		{
			out << book[i].record_num << " " << book[i].book_id << " " << book[i].book_name << " " << book[i].b_ptr
				<< " " << book[i].author << " " << book[i].w_ptr << " " << book[i].press << " " << book[i].p_ptr << " "
				<< book[i].classfity << " " << book[i].collect << " " << book[i].borrow;  //写入数据
			if (i != book.size() - 1)
				out << endl;
		}
	}
	out.close();         //关闭
}

//主菜单
int mainmenu()
{
	int n;
	cout << "-----图书管理系统----" << endl;
	cout << "-    1.读入文件	 -" << endl;
	cout << "-    2.图书查询	 -" << endl;
	cout << "-    3.添加图书	 -" << endl;
	cout << "-    0.退出系统	 -" << endl;
	cout << "---------------------" << endl;
	cout << "输入数字选择功能" << endl;
	cin >> n;
	return n;
}

void Delete()
{

}

void borrow_book()
{

}

void return_book()
{

}

void add_reader()
{

}

void delete_reader()
{

}

void outreaderfile()
{
	ofstream out("reader_message.txt");
	if (!out) {             //是否正常打开
		cout << "error";
	}
	else {
		for (int i = 0; i < reader.size(); i++)
		{
			out << reader[i].name << " "
				<< reader[i].reader_num << " "
				<< reader[i].bn1 << " "
				<< reader[i].bn2;
			if (i != book.size() - 1)
				out << endl;
		}
	}
	out.close();         //关闭 
}

void outBRfile()
{
	ofstream out("bollow_message.txt");
	if (!out) {             //是否正常打开
		cout << "error";
	}
	else {
		for (int i = 0; i < bbook.size(); i++)
		{
			out << bbook[i].book_id << " "
				<< bbook[i].reader_num << " "
				<< bbook[i].borrow_date << " "
				<< bbook[i].return_date;
			if (i != book.size() - 1)
				out << endl;
		}
	}
	out.close();         //关闭 
}