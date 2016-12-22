use qx;

create table if not exists year_average
( year smallint,
  average float);

create table if not exists month_average
( year smallint,
  average float);

delimiter $$
create procedure avg_month()
begin
set @vyear =1951;
set @vmonth = 1;
/*insert into month_average select avg(average) from source_data where year=@vyear and month=@vmonth;
*/
select avg(average) from source_data where year=@vyear and month=@vmonth;
end
$$
delimiter;
