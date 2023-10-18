explain select customerid 
	from customers 
	where customerid not in (   select customerid   from orders   where status='Paid' );  
 
explain select customerid 
	from 
		(select customerid   
			from customers   union all   select customerid   from orders   where status='Paid' ) 
			as A group by customerid having count(*) =1;  
 
explain select customerid from customers except   select customerid   from orders   where status='Paid';
            
            