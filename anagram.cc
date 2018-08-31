#include <fstream>
#include <bits/stdc++.h>
#include <map>

using namespace std;
/*
  Comment the following line when running in HackerRank.
  Otherwise read the input from a file 'anagram.data'.
*/
#define DEBUG 1

int factorial(int n) { return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n; }
int comb(int n) { return n*(n-1) / 2; }

void subStrings(string str, int n, map<int, vector<string>> &size_substr)
{
  // Pick starting point
  for (int len = 1; len <= n; len++) 
    {    
      // Pick ending point
      for (int i = 0; i <= n - len; i++) 
        {
          // Print characters from current
          // starting point to current ending
          // point.  
          int j = i + len - 1;
          if (size_substr.find(len) == size_substr.end())
            size_substr[len] = vector<string>(1, str.substr(i, len));
          else {
            size_substr[len].push_back(str.substr(i, len));
          }
        }
    }
}

int number_anagrams (string str, int n)
{
  map<int, vector<string>> size_substr;
  subStrings(str, n, size_substr);
  int multiplicity = 0;
  for (size_t i=1;i<n;++i) {
    map<string, long> freq;
    for (auto &e : size_substr[i]) sort(e.begin(), e.end());
    for (const auto &e : size_substr[i]) {
      if (freq.find(e) == freq.end())
        freq[e] = 1;
      else
        freq[e] += 1;
    }
    for (const auto &e : size_substr[i]) if (freq[e] == 1) freq.erase(e);
  
    for (const auto &e : freq) {
      // cout << e.first << " (" << comb(e.second) << ")" << endl;
      multiplicity += comb(e.second);
    }
  }
  cout << multiplicity << endl;

  return multiplicity;
}

// Complete the sherlockAndAnagrams function below.
int sherlockAndAnagrams(string s) {
  return number_anagrams(s, s.size());
}

int main()
{
#ifdef DEBUG
  ifstream inFile; 
  inFile.open("anagram.data");
#define INFILE inFile
#else
#define INFILE cin
#endif  
  int q;
  INFILE >> q;
  INFILE.ignore(numeric_limits<streamsize>::max(), '\n');
  for (int q_itr = 0; q_itr < q; q_itr++) {
    string s;
    getline(INFILE, s);
    sherlockAndAnagrams(s);
  }
#ifdef DEBUG
  INFILE.close();
#endif  
  return 0;
}
