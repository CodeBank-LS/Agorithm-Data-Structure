//using MST 
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <string>

using namespace std;

struct Vertex
{
    int id;
    int d;
    int parent;
};

class Puzzle
{
private:
    vector<vector<int>> country;
    vector<vector<int>> build;
    vector<vector<int>> destroy;
    vector<vector<int>> weight;

    vector<string> split(const string &s, const string &delimiters = " ")
    {
        vector<string> tokens;
        auto last_pos = s.find_first_not_of(delimiters, 0);
        auto pos = s.find_first_of(delimiters, last_pos);
        while (string::npos != pos || string::npos != last_pos)
        {
            tokens.emplace_back(s.substr(last_pos, pos - last_pos));
            last_pos = s.find_first_not_of(delimiters, pos);
            pos = s.find_first_of(delimiters, last_pos);
        }
        return tokens;
    }

    int get_value(char c)
    {
        if (c == '0')
            return 0;
        else if (c == '1')
            return 1;
        else if (c >= 'A' && c <= 'Z')
            return c - 'A';
        else
            return c - 'a' +26;
    }

    vector<vector<int>> parse_input(const string &str)
    {
        vector<vector<int>> matrix;
        auto toks = split(str, ",");
        for (auto &&i : toks)
        {
            vector<int> row;
            for (auto &&j : i)
            {
                row.emplace_back(get_value(j));
            }
            matrix.emplace_back(row);
        }
        return matrix;
    }

    vector<vector<int>> weight_new()
    {
        int n = country.size();
        vector<vector<int>> w(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                w[i][j] = country[i][j]? -destroy[i][j]:build[i][j];
            }
        }
        return w;
    }

    void print_matrix(const vector<vector<int>> &m)
    {
        for (auto &&i : m)
        {
            for (auto &&j : i)
                cout << j << " ";
            cout << "\n";
        }
    }

    int cal_cost(const vector<int> &parent)
    {
        int n = country.size();
        int c = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
            {
                if (parent[i] == j || parent[j] == i)
                {
                    c += country[i][j] == 0 ? build[i][j] : 0;
                }
                else
                {
                    c += country[i][j] == 1 ? destroy[i][j] : 0;
                }
            }

        return c;
    }

    vector<int> mst_prim()
    {
        int n = country.size();
        vector<int> d(n, INT32_MAX);
        vector<int> parent(n, -1);
        vector<int> inG(n, 1);

        auto comp = [&d](const int l, const int r)
        {
            return d[l] > d[r];
            // return l>r;
        };
        priority_queue<int, vector<int>, decltype(comp)> Q(comp);

        d[0] = 0;


        Q.push(0);
        while (!Q.empty())
        {
            int u = Q.top();
            Q.pop();
            inG[u] = 0;
            for (int v = 0; v < n; v++)
            {
                if (inG[v] && weight[u][v] < d[v])
                {
                    parent[v] = u;
                    d[v] = weight[u][v];
                    Q.push(v);
                }
            }
        }

        return parent;
    }

public:
    Puzzle(string input);
    ~Puzzle();
    void print_info();
    void getCost();
};

Puzzle::Puzzle(const string input)
{
    auto toks = split(input, " ");
    country = parse_input(toks[0]);
    build = parse_input(toks[1]);
    destroy = parse_input(toks[2]);

    weight = weight_new();
}

Puzzle::~Puzzle()
{
}

void Puzzle::getCost()
{
    auto p=mst_prim();
    auto cost=cal_cost(p);
    cout<<cost<<endl;
}

void Puzzle::print_info()
{
    cout << "country:" << endl;
    print_matrix(country);
    cout << "build:" << endl;
    print_matrix(build);
    cout << "destroy:" << endl;
    print_matrix(destroy);
    cout << "weight_new:" << endl;
    print_matrix(weight);

}

int main(int argc, char const *argv[])
{

    string input;
    getline(cin,input);

    Puzzle puzzle(input);
    //puzzle.print_info();
    puzzle.getCost();


    return 0;
}
