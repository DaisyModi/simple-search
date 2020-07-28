# CPP1_5

# Requirements:
C++17
Visual Studio

Platform-specific:
MAC: Boost

# Application Features:
1.	Error handling for input string. 
2.	The search is case insensitive.
3.	Autocomplete query in batches of 10.
4.	For exact match enclose the query in double quotes.
5.	Stemming : * represents zero or more characters. Queries ending or beginning with * can be searched.
6.	Logical connectors AND, OR are permitted in query.
7.	Phrases can be searched.
8.	Complex queries can be cascaded with logical connectors AND, OR to any level. It can include stemming, phrase, word as well as exact match.
9.	Horizontal and Vertical Collations results can be displayed as per the user.


# How to Use ?

1.	After launching the application , the user is prompted to enter the directory path in which the preferred text files to search are located.
2.	3 options in the following order are given: 
•	Autocomplete,
•	Search,
•	Exit
2.	If the user chooses autocomplete, first 10 words (if more than 10 words applicable) are displayed. User will be asked if next set of words is desired.
3.	Under search, user can enter any type of query: 
•	Exact Search : Enclosed the input query in double quotes.
•	Phrase : Give space separated words enclosed in double quotes as input.
•	Stemming : Input a query with word ending or beginning with *. Ex: *ect or proj*
•	Logical Query : Input a query in format a connector b connector c …., where word can be any of the above type of queries.


