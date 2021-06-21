#include <bits/stdc++.h>

using namespace std;

#define db(...) __internal_multi_debug(0, false, #__VA_ARGS__, __VA_ARGS__)
#define dbl(...) __internal_multi_debug(0, true, #__VA_ARGS__, __VA_ARGS__)
#define dbg(...) cout << __internal_set_variable_name(#__VA_ARGS__) << __internal_function_debug(__VA_ARGS__) << "\n"
#define dbm(...) __debug_array_main(#__VA_ARGS__, __VA_ARGS__)
#define dbs(...) __debug_single_main(#__VA_ARGS__, __VA_ARGS__)
#define dbas(...) __convert_basis(#__VA_ARGS__, __VA_ARGS__)

bool __internal_is_not_primitive_data = false;
bool __internal_in_debug = false;
int __internal_depth = 0;
vector<string> __internal_direction_path;
string __internal_debug_response;

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

string to_string(char c)
{
    string s;
    s += c;
    return "'" + s + "'";
}

string to_string(string s)
{
    return '"' + s + '"';
}

string to_string(const char* s)
{
    return to_string((string)s);
}

string to_string(bool b)
{
    return (b ? "true" : "false");
}

template <typename A>
string to_string(complex<A> c)
{
    pair<A,A> p = {c.real(), c.imag()};
    return to_string(p);
}

string to_string(vector<bool> v)
{
    if(__internal_depth <= 0 && __internal_in_debug)
    {
        __internal_in_debug = false;
        __internal_debug_response += __internal_direction_path.back() + ": " + to_string(v) + "\n";
        __internal_in_debug = true;
        return "";
    }
    bool first = true;
    string res = "{";
    int cont = 0;
    for(int i = 0 ; i < static_cast<int>(v.size()) ; i++)
    {
        if(!first)
        {
            res += ", ";
        }
        first = false;
        string temp = __internal_direction_path.back();
        __internal_depth--;
        __internal_direction_path.back() += "[" + to_string(cont) + "]";
        __internal_is_not_primitive_data = false;
        res += to_string(v[i]);
        __internal_depth++;
        if(!__internal_is_not_primitive_data && __internal_in_debug)
        {
            __internal_debug_response += __internal_direction_path.back() + ": " + to_string(v[i]) + "\n";
        }
        __internal_direction_path.back() = temp;
        cont++;
    }
    res += "}";
    __internal_is_not_primitive_data = true;
    return res;
}

template <size_t N>
string to_string(bitset<N> v)
{
    string res = "";
    for(size_t i = 0 ; i < N ; i++)
    {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A>
string to_string(A v)
{
    if(__internal_depth <= 0 && __internal_in_debug)
    {
        __internal_in_debug = false;
        __internal_debug_response += __internal_direction_path.back() + ": " + to_string(v) + "\n";
        __internal_in_debug = true;
        return "";
    }
    bool first = true;
    string res = "{";
    int cont = 0;
    for(auto &x : v)
    {
        if(!first)
        {
            res += ", ";
        }
        first = false;
        string temp = __internal_direction_path.back();
        __internal_depth--;
        __internal_direction_path.back() += "[" + to_string(cont) + "]";
        __internal_is_not_primitive_data = false;
        res += to_string(x);
        __internal_depth++;
        if(!__internal_is_not_primitive_data && __internal_in_debug)
        {
            __internal_debug_response += __internal_direction_path.back() + ": " + to_string(x) + "\n";
        }
        __internal_direction_path.back() = temp;
        cont++;
    }
    res += "}";
    __internal_is_not_primitive_data = true;
    return res;
}

template <typename A>
string to_string(stack<A> s)
{
    vector<A> v;
    while(!s.empty())
    {
        v.push_back(s.top());
        s.pop();
    }
    reverse(v.begin(),v.end());
    return to_string(v);
}

template <typename A>
string to_string(queue<A> q)
{
    vector<A> v;
    while(!q.empty())
    {
        v.push_back(q.front());
        q.pop();
    }
    return to_string(v);
}

template <typename A>
string to_string(priority_queue<A> pq)
{
    vector<A> v;
    while(!pq.empty())
    {
        v.push_back(pq.top());
        pq.pop();
    }
    return to_string(v);
}

vector<string> __parsing(string cad)
{
    vector<string> vect;

    int level = 0;
    bool inexpress1 = false;
    bool inexpress2 = false;

    function<void(string&)> delallspace = [&](string &cad)
    {
        string temp;

        for(int i = 0 ; i < cad.size() ; i++)
        {
            if(cad[i] == ' ')continue;
            temp += cad[i];
        }

        cad = temp;
    };

    function<void(string&)> delspace = [&](string &cad)
    {
        while(cad.size() && cad.back() == ' ')cad.pop_back();

        reverse(cad.begin(), cad.end());

        while(cad.size() && cad.back() == ' ')cad.pop_back();

        reverse(cad.begin(), cad.end());
    };

    function<bool(char)> isopen = [&](char c)
    {
        if(c == '(')return true;
        if(c == '{')return true;
        if(c == '[')return true;
        // if(c == '<')return true;
        return false;
    };

    function<bool(char)> isclose = [&](char c)
    {
        if(c == ')')return true;
        if(c == '}')return true;
        if(c == ']')return true;
        // if(c == '>')return true;
        return false;
    };

    string temp;

    for(int i = 0 ; i < cad.size() ; i++)
    {
        temp += cad[i];
        if(!inexpress1 && !inexpress2)
        {
            if(isopen(cad[i]))level++;
            else if(isclose(cad[i]))level--;
            else if(cad[i] == '\"')inexpress1 = true;
            else if(cad[i] == '\'')inexpress2 = true;
            else if(level == 0 && cad[i] == ',')
            {
                temp.pop_back();
                vect.push_back(temp);
                temp.clear();
            }
        }
        else
        {
            if(inexpress1 && cad[i] == '\"' && cad[i-1] != '\\')inexpress1 = false;
            else if(inexpress2 && cad[i] == '\'' && cad[i-1] != '\\')inexpress2 = false;
        }
    }

    vect.push_back(temp);
    temp.clear();

    for(int i = 0 ; i < vect.size() ; i++)
    {
        delspace(vect[i]);
    }

    return vect;
}

string __internal_set_variable_name()
{
    return "";
}

string __internal_set_variable_name(string cad)
{
    vector<string> vect = __parsing(cad);

    cad = vect[0];
    
    __internal_direction_path.push_back(cad);
    return "";
}

string __internal_set_depth()
{
    __internal_depth = 0;
    return "";
}

string __internal_set_depth(int n)
{
    __internal_depth = n;
    return "";
}

string __internal_function_debug()
{
    return "\n";
}

template <typename A, typename... Args>
string __internal_function_debug(A v, Args... args)
{
    __internal_set_depth(args...);
    __internal_is_not_primitive_data = false;
    string res = to_string(v);
    if(!__internal_is_not_primitive_data)
    {
        string cad = __internal_direction_path.back();
        __internal_direction_path.pop_back();
        return cad + ": " + res + "\n";
    }
    __internal_in_debug = true;
    __internal_debug_response.clear();
    to_string(v);
    __internal_in_debug = false;
    __internal_direction_path.pop_back();
    return __internal_debug_response;
}

void __internal_multi_debug(int it, bool space, string cad)
{
    return;
}

template <typename A, typename... Args>
void __internal_multi_debug(int it, bool space, string cad, A v, Args ... args)
{
    vector<string> vect = __parsing(cad);

    cout << __internal_set_variable_name(vect[it]);
    string temp = __internal_function_debug(v);
    if(space)
    {
        if(it+1 != vect.size())temp.pop_back();
        if(it)temp = ", " + temp;
    }
    if(it+1 == vect.size())temp += "\n";
    cout << temp;
    __internal_multi_debug(it+1, space, cad, args...);
    return;
}

template <typename A, typename B>
string to_string(pair<A, B> p)
{
    if(__internal_in_debug)
    {
        __internal_in_debug = false;
        string res = "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
        __internal_in_debug = true;
        __internal_is_not_primitive_data = false;
        return res;
    }
    string res = "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
    __internal_is_not_primitive_data = false;
    return res;
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p)
{
    if(__internal_in_debug)
    {
        __internal_in_debug = false;
        string res = "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
        __internal_in_debug = true;
        __internal_is_not_primitive_data = false;
        return res;
    }
    string res = "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
    __internal_is_not_primitive_data = false;
    return res;
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p)
{
    if(__internal_in_debug)
    {
        __internal_in_debug = false;
        string res = "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
        __internal_in_debug = true;
        __internal_is_not_primitive_data = false;
        return res;
    }
    string res = "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
    __internal_is_not_primitive_data = false;
    return res;
}

string __convert_basis(long long num, long long bas, long long prec, bool rev)
{
    string res;

    if(!num)
    {
        res = "0";
        return res;
    }

    if(bas <= 10)
    {
        if(prec == -1)
        {
            while(num)
            {
                res += (char)('0' + num%bas);
                num /= bas;
            }
            reverse(res.begin(), res.end());
        }
        else
        {
            for(int i = 0 ; i < prec ; i++)
            {
                res += (char)('0' + num%bas);
                num /= bas;
            }
            reverse(res.begin(), res.end());
        }
    }
    else if(bas == 16)
    {
        vector<char> nhex;
        for(int i = '0' ; i <= '9' ; i++)
        {
            nhex.push_back(i);
        }
        for(int i = 'A' ; i <= 'F' ; i++)
        {
            nhex.push_back(i);
        }
        
        if(prec == -1)
        {
            while(num)
            {
                res += nhex[num%bas];
                num /= bas;
            }
            reverse(res.begin(), res.end());
        }
        else
        {
            for(int i = 0 ; i < prec ; i++)
            {
                res += nhex[num%bas];
                num /= bas;
            }
            reverse(res.begin(), res.end());
        }
    }
    else
    {
        if(prec == -1)
        {
            while(num)
            {
                res += "." + to_string(num%bas);
                num /= bas;
            }
            reverse(res.begin(), res.end());
        }
        else
        {
            for(int i = 0 ; i < prec ; i++)
            {
                res += "." + to_string(num%bas);
                num /= bas;
            }
            reverse(res.begin(), res.end());
        }
        
        res.pop_back();
    }

    if(rev)
    {
        reverse(res.begin(), res.end());
    }

    return res;
}

void __convert_basis(string cad, long long num, long long bas = 2, long long prec = -1, bool rev = false)
{
    assert(num >= 0);
    assert(bas >= 2);
    assert(prec >= 1 || prec == -1);

    vector<string> vect = __parsing(cad);

    cout << vect[0] << ": " << __convert_basis(num, bas, prec, rev) << '\n' << '\n';
}

template <typename A, typename... Args>
int __debug_array(vector<pair<vector<int>,string>> &vvv, vector<int> &dim, A v)
{
    vvv.push_back({dim, to_string(v)});
    return 0;
}

template <typename A, typename... Args>
int __debug_array(vector<pair<vector<int>,string>> &vvv, vector<int> &dim, A v, int depth)
{
    vvv.push_back({dim, to_string(v)});
    return depth;
}

template <typename A, typename... Args>
int __debug_array(vector<pair<vector<int>,string>> &vvv, vector<int> &dim, A arr, int a, int b, Args ... args)
{
    int tp = 0;
    for(int i = a ; i <= b ; i++)
    {
        dim.push_back(i);
        int val = __debug_array(vvv, dim, arr[i], args...);
        if(val)tp = val;
        dim.pop_back();
    }
    return tp;
}

template <typename A, typename... Args>
void __debug_array_main(string cad, A arr, Args ... args)
{
    vector<string> vect = __parsing(cad);

    vector<pair<vector<int>,string>> vvv;

    vector<int> dim;

    int depth = __debug_array(vvv, dim, arr, args...);

    if(!vvv.size())return;

    vector<map<int,int>> T(1);
    vector<string> sss(1);

    for(auto ppp : vvv)
    {
        vector<int> temp = ppp.first;;
        string cad = ppp.second;

        int pt = 0;
        for(auto x : temp)
        {
            if(T[pt][x] == 0)
            {
                T[pt][x] = T.size();
                T.emplace_back();
                sss.emplace_back();
            }
            pt = T[pt][x];
        }

        sss[pt] = cad;
    }

    string res;

    function<string(int,int,string)> DFS = [&](int nodo, int depth, string pth)
    {
        if(T[nodo].size() == 0)
        {
            if(depth > 0)res += pth + ": " + sss[nodo] + "\n";
            return sss[nodo];
        }

        bool first = true;

        string cad = "{";

        for(auto x : T[nodo])
        {
            int v = x.second;

            string tpth = pth + "[" + to_string(x.first) + "]";

            if(!first)
            {
                cad += ", ";
            }

            first = false;

            if(depth-1 > 0)
            {
                DFS(v, depth-1, tpth);
            }
            else if(depth-1 == 0)
            {
                res += tpth + ": " + DFS(v, depth-1, tpth) + "\n";
            }
            else 
            {
                cad += DFS(v, depth-1, tpth);
            }
        }

        cad += "}";

        return cad;
    };

    if(depth <= 0)
    {
        res = DFS(0, depth, vect[0]);
        cout << vect[0] << ": " << res << "\n" << "\n"; 
    }
    else
    {
        DFS(0, depth, vect[0]);
        cout << res << "\n";
    }
}

template <typename A, typename... Args>
string __debug_single(A arr)
{
    string res = ": " + to_string(arr) + "\n";
    return res;
}

template <typename A, typename... Args>
string __debug_single(A arr, int pos, Args ... args)
{
    string res = "[" + to_string(pos) + "]" + __debug_single(arr[pos], args...);
    return res;
}

template <typename A, typename... Args>
void __debug_single_main(string cad, A arr, Args ... args)
{
    vector<string> vect = __parsing(cad);
    string res = vect[0] + __debug_single(arr, args...);
    cout << res << "\n";
}

