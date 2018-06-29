#include <iostream>
#include <pqxx/pqxx>

using namespace std;

int main()
{
	try
	{
		pqxx::connection c("dbname=postgres hostaddr=127.0.0.1 user=beyondb password=123456");
		cout << "conncted to " << c.dbname() << endl;
		pqxx::work txn(c);

		txn.exec(
			"drop table if exists mytable;"
		);
		txn.exec(
		"create table mytable ("
		"id int not null,"
		"name varchar(255));"
		);
		txn.exec(
		"insert into mytable values("
			"1,'lisong');"
		);
		pqxx::result r = txn.exec(
			"select * from mytable;"
		);

		for (auto row = r.begin(); row != r.end(); row++)
		{
			cout << row[0].c_str() << "::" << row[1].c_str() << endl;
		}
		txn.commit();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		getchar();
		return 1;
	}

	getchar();
	return 0;
}