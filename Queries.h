#pragma once
void creation(vector<string>query);
void drop(string DBName, vector<string> splitedQuery);
void truncate(string DBName, vector<string>splitedQuery);
void QueryResult(string query, vector<string>result, int choice);