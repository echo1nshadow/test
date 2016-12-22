create database if not exists qx; /*创建数据库*/

use qx;     /*选中该数据库*/
create table if not exists source_data  /*创建原始数据表*/
(
 station mediumint,
 year    smallint,
 month   smallint,
 day     smallint,
 average smallint,
 max     smallint,
 min     smallint);

load data local infile "/home/echo/qx/data.txt" into table source_data fields terminated by ",";        /*从文件中导入数据*/
