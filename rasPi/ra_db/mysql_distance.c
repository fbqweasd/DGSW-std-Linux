#include <mariadb/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wiringPi.h>

extern float get_distance();

struct connection_details{
    char *server;
    char *user;
    char *password;
    char *database;
};
MYSQL* mysql_connection_setup(struct connection_details mysql_details){  
	MYSQL *connection = mysql_init(NULL);
	if (!mysql_real_connect(connection,mysql_details.server, 
			mysql_details.user, mysql_details.password, 
			mysql_details.database, 3306, NULL, 0)){
   	   printf("Conection error : %s\n", mysql_error(connection));
   	   exit(1);
	}
	return connection;
}

MYSQL_RES* mysql_perform_query(MYSQL *connection, char *sql_query){
        if (mysql_query(connection, sql_query)){
           printf("MySQL query error : %s\n", mysql_error(connection));
           exit(1);
         }
        return mysql_use_result(connection);
}

int main()
{
	int i=0;
	char id;
	char str3[BUFSIZ];
	MYSQL *conn;      // the connection
	MYSQL_RES *res;   // the results
	MYSQL_ROW row;    // the results row (line by line)
	struct connection_details mysqlD;
	mysqlD.server ="localhost";  // where the mysql database is
	mysqlD.user = "root";     // the root user of mysql   
	mysqlD.password = "dgsw"; // the password of the root user in mysql
	mysqlD.database = "mysql";    // the databse to pick
	// connect to the mysql database
	conn = mysql_connection_setup(mysqlD);
	// assign the results return to the MYSQL_RES pointer
	for(i=0;i<3;i++){
		sprintf(str3,"insert into test2(id,distance) values(\"%s\",\"%s\")",i,get_distance());
		delay(5);
	}
	mysql_free_result(res);
	mysql_close(conn);
       
	return 0;
}
