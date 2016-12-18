#include <iostream>
#include <vector>
#include <string>
using namespace std ;
bool edge[30][30] ;
int pred[30], succ[30] ;
int main() {
   char lastlet ;
   int nwords ;
   cin >> lastlet >> nwords ;
   string prev, w ;
   bool inconsistent = false ;
   int nlet = lastlet - 'a' + 1 ;
   for (int i=0; i<nwords; i++, prev=w) {
      cin >> w ;
      int d = 0 ;
      while (d < prev.size() && d < w.size() && prev[d] == w[d])
         d++ ;
      if (d >= prev.size())
         continue ;
      if (d >= w.size()) {
         inconsistent = 1 ;
         continue ;
      }
      if (edge[prev[d]-'a'][w[d]-'a'] == 0) {
         edge[prev[d]-'a'][w[d]-'a'] = 1 ;
         pred[w[d]-'a']++ ;
         succ[prev[d]-'a']++ ;
      }
   }
   string res ;
   bool insuff = false ;
   for (int i=0; i<nlet; i++) {
      int head = -1 ;
      for (int j=0; j<nlet; j++)
         if (pred[j] == 0) {
            if (head < 0)
               head = j ;
            else
               insuff = true ;
         }
      if (head < 0) {
         inconsistent = 1 ;
         break ;
      }
      pred[head] = -1 ;
      for (int j=0; j<nlet; j++)
         if (edge[head][j])
            pred[j]-- ;
      res.push_back(head + 'a') ;
   }
   if (insuff) {
      cout << "AMBIGUOUS" << endl ;
   } else if (inconsistent) {
      cout << "IMPOSSIBLE" << endl ;
   } else {
      cout << res << endl ;
   }
}

