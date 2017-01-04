//********************************************************************************
// Author           : Ramsundar K G - kgram007@gmail.com
// Online judge     : UVa Online Judge
// Problem ID/title : 10044 - Erdos Numbers
//********************************************************************************

#define __cplusplus 201103L

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <list>

using namespace std;

#define OPTIMIZED
#define ERDOS_STRING		"Erdos, P."

#ifdef OPTIMIZED
	#define ERDOS	0
#else
	#define ERDOS	ERDOS_STRING
#endif


#ifdef OPTIMIZED
	typedef int NodeType;
	typedef unordered_map< string, int > StringToIntMap;
	typedef unordered_map< int, string > IntToStringMap;

	int author_index_count = 0;
	StringToIntMap author_to_int;
	IntToStringMap int_to_author;
#else
	typedef string NodeType;
#endif

typedef unordered_set< NodeType > AdjacencyList;
typedef unordered_map< NodeType, AdjacencyList > Graph;


#ifdef OPTIMIZED
int mapAuthorInt(string author_name)
{
	int author_index;
	if( author_to_int.find(author_name) == author_to_int.end() )
	{
		author_index = author_index_count;
		author_to_int[ author_name ] = author_index;
		int_to_author[ author_index ] = author_name;
		author_index_count++;
	}
	else
	{
		author_index = author_to_int[ author_name ];
	}
	return author_index;
}
#endif


vector< NodeType > parseAuthors(string& papper)
{
	vector<NodeType> authors;
	string authors_str = papper.substr(0, papper.find(':'));
	size_t  start_pos = 0;
	while( start_pos < authors_str.length() )
	{
		size_t  first_comma = authors_str.find(',', start_pos);
		size_t  second_comma = authors_str.find(',', first_comma+1);
		string author_name = authors_str.substr(start_pos, second_comma-start_pos);

#ifdef OPTIMIZED
		int author_index = mapAuthorInt(author_name);
		authors.push_back(author_index);
#else
		authors.push_back(author_name);
#endif

		if(second_comma == string::npos)
			break;
		start_pos = second_comma + 2;
	}

	return authors;
}

NodeType getAuthor(string author_name)
{
#ifdef OPTIMIZED
	if( author_to_int.find(author_name) != author_to_int.end() ) // found
		return author_to_int[ author_name ];
	else
		return -1;
#else
	return author_name;
#endif
}

void insertGraph(Graph& author_graph, const vector< NodeType >& authors)
{
	for(int i=0; i<(int)authors.size()-1; ++i)
	{
		for(int j=i+1; j<(int)authors.size(); ++j)
		{
			NodeType author_i = authors[i];
			NodeType author_j = authors[j];
			if(author_i != author_j)
			{
				author_graph[ author_i ].insert( author_j );
				author_graph[ author_j ].insert( author_i );
			}
		}
	}
}

int findErdosNumber(Graph& author_graph, NodeType author_start)
{
#ifdef OPTIMIZED
	if(author_start < 0)
		return -1;
#else
	if( author_graph.find(author_start) == author_graph.end() )
		return -1;
#endif

    if(author_start == ERDOS)
    	return 0;

    // Mark all the vertices as not visited
	unordered_set< NodeType > visited;

    // Create a queue for BFS
    list< pair<NodeType, int> > queue;

    // Mark the current node as visited and enqueue it
    NodeType s = author_start;
    visited.insert(s);
    int level = 1;

    queue.push_back( pair<NodeType, int>(s, level) );

    while( !queue.empty() )
    {
        // Dequeue a vertex from queue and print it
    	s = queue.front().first;
    	level = queue.front().second;
        queue.pop_front();

        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for(NodeType author: author_graph[s])
        {
	        if(author == ERDOS)
	        	return level;

			if( visited.find(author) == visited.end() )
			{
				visited.insert(author);
				queue.push_back( pair<NodeType, int>(author, level+1) );
			}
        }
    }

    return -1;
}

void init()
{
#ifdef OPTIMIZED
	mapAuthorInt(ERDOS_STRING);
#endif
}

int main()
{
	init();

	int scenarios;
	cin >> scenarios;
	for(int s = 1; s<=scenarios; ++s)
	{
		cout << "Scenario "  << s << endl;

		int P, N;
		cin >> P >> N;
		Graph author_graph;
		for(int p=0; p<P; ++p)
		{
			string papper;
			getline(cin, papper);
			if(papper.empty())
				{ p--; continue; }

			vector< NodeType > authors = parseAuthors(papper);

			insertGraph(author_graph, authors);
		}

		for(int n=0; n<N; ++n)
		{
			string author_n;
			getline(cin, author_n);
			if(author_n.empty())
				{ n--; continue; }

			int erdos_num = findErdosNumber(author_graph, getAuthor(author_n) );
			if(erdos_num >= 0)
				cout << author_n << " " << erdos_num << endl;
			else
				cout << author_n << " " << "infinity" << endl;
		}
	}

	return 0;
}
