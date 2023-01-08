#pragma once
void creation(vector<string>query);
void drop(string DBName, vector<string> splitedQuery);
void truncate(string DBName, vector<string>splitedQuery);
void SelectQuery(vector<string>the_query, string db_name);
void the_insert(vector<string>the_query, string db_name);
void QueryResult(string query, vector<string>result, int choice);