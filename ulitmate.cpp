#include <bits/stdc++.h>
#define MAX 0x3f3f3f3f

using namespace std;

ifstream fin("dfs.in");
ofstream fout("dfs.out");

bool SortParam(const pair<pair<int, int>, int> &x, const pair<pair<int, int>, int> &y)
{
  return (x.second < y.second);
}

class Graf
{
private:
  int N, M, diametru, nodStart;
  int adj3[101][101];
  vector<vector<int>> adc, adc2;
  vector<int> viz, dist, sortate, parinte, rank, vizite, circuit;
  vector<pair<pair<int, int>, int>> adj;
  vector<pair<int, int>> sol;
  vector<vector<pair<int, int>>> adj2;
  vector<bool> viz2;

  void Dfs(int);
  void Bfs(int);
  void DfsSortare(int);
  void DfsTareConexe(int node, vector<int> &a);
  void royFloyd();
  void dfsDarb(int, int);
  void Euler();

public:
  Graf(int);
  Graf(int, int);
  void AdaugaMuchieNeorientata(int, int);
  void AdaugaMuchieOrientata(int, int);
  int CompConexe();
  void Distanta(int);
  void Sortare();
  void adaugaMuchieCTC( int, int);
  vector<int> SortareCTC();
  void CompTareConexe();
  static bool VerifHavHak(vector<int> a);
  void adaugaMuchieAPM(int, int, int); //se inverseaza valorile pt citirea disjoint
  void Kruskall();
  void Leaga(int, int);
  int Gaseste(int);
  void Disjoint();
  void adaugaMuchieDijkstra(int, int, int);
  void Dijkstra(int);
  void BellmanFord(int);
  void adaugaMuchieRoyFloyd();
  void AfisareRoyFloyd();
  int AfisareDarb();
  void adaugaMuchieEuler(int, int, int);
  void AfiseazaEuler();
  ~Graf();
};

void Graf ::Dfs(int nod)
{
  int i, w;
  viz[nod] = 1;
  for (i = 0; i < adc[nod].size(); i++)
  {
    w = adc[nod][i];
    if (viz[w] == 0)
      Dfs(w);
  }
}

void Graf ::Bfs(int nod)
{
  int i, w, pr;
  queue<int> Q;
  for (i = 1; i <= N; i++)
    dist[i] = -1;
  dist[nod] = 0;
  Q.push(nod);
  while (!Q.empty())
  {
    pr = Q.front();
    Q.pop();
    for (i = 0; i < adc[pr].size(); i++)
    {
      w = adc[pr][i];
      if (dist[w] == -1)
      {
        dist[w] = dist[pr] + 1;
        Q.push(w);
      }
    }
  }
}

void Graf ::DfsSortare(int nod)
{
  int i, w;
  viz[nod] = 1;
  for (i = 0; i < adc[nod].size(); i++)
  {
    w = adc[nod][i];
    if (viz[w] == 0)
      DfsSortare(w);
  }
  sortate.push_back(nod);
}

void Graf ::DfsTareConexe(int nod, vector<int> &a)
{
  viz[nod] = 1;
  for (int i = 0; i < adc2[nod].size(); i++)
  {
    int w = adc2[nod][i];
    if (viz[w] == 0)
      DfsTareConexe(w, a);
  }
  a.push_back(nod);
}

void Graf ::royFloyd()
{
  int i, j, l;
  for (l = 0; l < N; l++)
    for (i = 0; i < N; i++)
      for (j = 0; j < N; j++)
        if (i != j && adj3[i][l] != INT_MAX && adj3[l][j] != INT_MAX)
          adj3[i][j] = min(adj3[i][j], (adj3[i][l] + adj3[l][j]));
}

void Graf ::dfsDarb(int x, int d)
{
  if (d > diametru)
  {
    diametru = d;
    nodStart = x;
  }

  viz[x] = 1;
  for (auto i : adc[x])
    if (!viz[i])
      dfsDarb(i, d + 1);
}

void Graf::Euler()
{
  int i, curr;
  stack<int> stk;

  for (i = 0; i < N; ++i)
    if (adj2[i].size() & 1)
    {
      fout << -1;
      return;
    }

  stk.push(1);

  while (!stk.empty())
  {
    curr = stk.top();

    if (adj2[curr].size())
    {
      pair<int, int> e = adj2[curr].back();
      adj2[curr].pop_back();

      if (!viz2[e.second])
      {
        viz2[e.second] = true;
        stk.push(e.first);
      }
    }
    else
    {
      stk.pop();
      circuit.push_back(curr);
    }
  }
}

Graf ::Graf(int n)
{
  N = n;
  adc.resize(n + 1);
  adc2.resize(n + 1);
  viz.resize(n + 1);
  dist.resize(n + 1);
  parinte.resize(n + 1);
  rank.resize(n + 1);
  adj2.resize(n + 1);
  vizite.resize(n + 1);
}

Graf ::Graf(int n, int m)
{
  N = n;
  M = m;
  adc.resize(n + 1);
  adc2.resize(n + 1);
  viz.resize(n + 1);
  dist.resize(n + 1);
  parinte.resize(n + 1);
  rank.resize(n + 1);
  adj2.resize(n + 1);
  vizite.resize(n + 1);
  viz2.resize(m + 1);
}

void Graf ::AdaugaMuchieNeorientata(int x, int y)
{
  adc[x].push_back(y);
  adc[y].push_back(x);
}

int Graf ::CompConexe()
{
  int i, conexe;
  conexe = 0;
  for (i = 1; i <= N; i++)
    viz[i] = 0;
  for (i = 1; i <= N; i++)
    if (viz[i] == 0)
    {
      Dfs(i);
      ++conexe;
    }
  return conexe;
}

void Graf ::AdaugaMuchieOrientata(int x, int y)
{
  adc[x].push_back(y);
}

void Graf ::Distanta(int s)
{
  int i;
  Bfs(s);
  for (i = 1; i <= N; i++)
    fout << dist[i] << " ";
}

void Graf ::Sortare()
{
  int i;
  sortate.clear();
  for (i = 1; i <= N; i++)
    viz[i] = 0;
  for (i = 1; i <= N; i++)
    if (viz[i] == 0)
      DfsSortare(i);
  for (i = sortate.size() - 1; i >= 0; i--)
    fout << sortate[i] << " ";
}

void Graf :: adaugaMuchieCTC(int x, int y) {
    adc[x].push_back(y);
    adc2[y].push_back(x);
}

vector<int> Graf ::SortareCTC()
{
  for (int i = 1; i <= N; i++)
    viz[i] = 0;
  for (int i = 1; i <= N; i++)
    if (viz[i] == 0)
      DfsSortare(i);
  return sortate;
}

void Graf ::CompTareConexe()
{
  vector<vector<int>> a;
  vector<int> v_sortat = SortareCTC();
  int curr, i, j;
  for (i = 0; i <= N; i++)
    viz[i] = 0;
  for (i = v_sortat.size() - 1; i >= 0; i--)
  {
    vector<int> ctc;
    curr = v_sortat[i];
    if (viz[curr])
      continue;
    DfsTareConexe(curr, ctc);
    a.push_back(ctc);
  }
  fout << a.size() << "\n";
  for (i = 0; i < a.size(); i++)
  {
    for (j = 0; j < a[i].size(); j++)
      fout << a[i][j] << " ";
    fout << "\n";
  }
}

bool Graf ::VerifHavHak(vector<int> a)
{
  int x, i;
  while (1)
  {
    sort(a.begin(), a.end());
    if (a.back() == 0) //daca toate elem sunt egale cu 0
      return true;
    x = a.back();
    a.pop_back();     //se sterge ultimul elem din lista
    if (x > a.size()) //lista trebuie sa contina destule valori
      return false;
    for (i = 0; i < x; i++)
    {
      a[i]--;
      if (a[i] < 0) //daca elem curent devine 0 -> fals
        return false;
    }
  }
}

void Graf ::adaugaMuchieAPM(int x, int y, int w)
{
  adj.push_back(make_pair(make_pair(x, y), w));
}

int Graf ::Gaseste(int x)
{
  if (x == parinte[x])
    return x;
  return Gaseste(parinte[x]);
}

void Graf::Leaga(int a, int b)
{
  int x = Gaseste(a);
  int y = Gaseste(b);

  if (rank[x] >= rank[y])
  {
    parinte[y] = x;
    rank[x] += rank[y];
    M++;
  }
  else
  {
    parinte[x] = y;
    rank[y] += rank[x];
    M++;
  }
}
void Graf ::Kruskall()
{
  int cost = 0, i, x, y, a, b;
  M = 0;

  for (i = 1; i <= N; i++)
  {
    parinte[i] = i;
    rank[i] = 1;
  }
  sort(adj.begin(), adj.end(), SortParam);
  for (i = 0; i < adj.size(); i++)
  {
    x = Gaseste(adj[i].first.first);
    y = Gaseste(adj[i].first.second);
    a = adj[i].first.first;
    b = adj[i].first.second;
    if (x != y)
    {
      sol.push_back(make_pair(b, a));
      Leaga(b, a);
      cost += adj[i].second;
    }
  }
  fout << cost << '\n';
  fout << M << '\n';
  for (i = 0; i < M; i++)
    fout << sol[i].first << ' ' << sol[i].second << '\n';
}

void Graf ::Disjoint()
{
  int i, w, x, y;
  for (i = 1; i <= N; i++)
  {
    parinte[i] = i;
    rank[i] = 1;
  }

  for (i = 0; i < adj.size(); i++)
  {
    w = adj[i].first.first;
    x = adj[i].first.second;
    y = adj[i].second;
    if (w == 1)
      Leaga(x, y);
    else if (Gaseste(x) == Gaseste(y))
      fout << "DA\n";
    else
      fout << "NU\n";
  }
}

void Graf ::adaugaMuchieDijkstra(int x, int y, int w)
{
  adj2[x].push_back(make_pair(y, w));
}

void Graf ::Dijkstra(int x)
{
  int i;
  for (i = 1; i <= N; i++)
    dist[i] = MAX;
  dist[x] = 0;
  priority_queue<pair<int, int>> q;
  q.push(make_pair(0, x));
  while (!q.empty())
  {
    int nod = q.top().second;
    q.pop();
    if (viz[nod] == true)
      continue;
    else
      viz[nod] = true;
    for (auto curr : adj2[nod])
    {
      if (dist[nod] + curr.second < dist[curr.first])
      {
        dist[curr.first] = dist[nod] + curr.second;
        q.push(make_pair(-dist[curr.first], curr.first));
      }
    }
  }
  for (i = 2; i <= N; i++)
    if (dist[i] != MAX)
      fout << dist[i] << " ";
    else
      fout << 0 << " ";
}

void Graf ::BellmanFord(int x)
{
  int i;
  for (i = 1; i <= N; i++)
    dist[i] = MAX;
  dist[x] = 0;
  priority_queue<pair<int, int>> q;
  q.push(make_pair(0, x));
  while (!q.empty())
  {
    int nod = q.top().second;
    q.pop();
    vizite[nod]++;
    if (vizite[nod] == N)
    {
      fout << "Ciclu negativ!";
      return;
    }
    for (auto curr : adj2[nod])
    {
      if (dist[nod] + curr.second < dist[curr.first])
      {
        dist[curr.first] = dist[nod] + curr.second;
        q.push(make_pair(-dist[curr.first], curr.first));
      }
    }
  }
  for (i = 2; i <= N; i++)
    if (dist[i] != MAX)
      fout << dist[i] << " ";
    else
      fout << 0 << " ";
}

void Graf ::adaugaMuchieRoyFloyd()
{
  int i, j;
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
    {
      fin >> adj3[i][j];
      if (i != j && adj3[i][j] == 0)
        adj3[i][j] = INT_MAX;
    }
  }
}

void Graf ::AfisareRoyFloyd()
{
  int i, j;
  royFloyd();
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N; j++)
      fout << adj3[i][j] << " ";
    fout << "\n";
  }
}

int Graf ::AfisareDarb()
{
  int i;
  dfsDarb(1, 1);
  for (i = 0; i < N; i++)
    viz[i] = 0;
  diametru = 0;
  dfsDarb(nodStart, 1);
  return diametru;
}

void Graf::adaugaMuchieEuler(int x, int y, int i)
{
  adj2[x].push_back(make_pair(y, i));
  adj2[y].push_back(make_pair(x, i));
}

void Graf::AfiseazaEuler()
{
  Euler();
  for (auto i : circuit)
    fout << i << " ";
}

Graf :: ~Graf()
{
  N = 0;
  M = 0;
  adc.clear();
  adc2.clear();
  viz.clear();
  dist.clear();
  parinte.clear();
  rank.clear();
  adj2.clear();
  vizite.clear();
  viz2.clear();
}

int main()
{

  //DFS
  
  int n, m, x, y, i;
  fin >> n >> m;
  Graf G(n);
  for (i = 1; i <= m; i++)
  {
    fin >> x >> y;
    G.AdaugaMuchieNeorientata(x, y);
  }
  fout << G.CompConexe();

  //BFS
  
  /*int n, m, s, x, y, i;
  fin >> n >> m >> s;
  Graf G(n);
  for (i = 1; i <= m; i++)
  {
    fin >> x >> y;
    G.AdaugaMuchieOrientata(x, y);
  }
  G.Distanta(s);

  //SortareTopologica

  int n, m, x, y, i;
  fin >> n >> m;
  Graf G(n);
  for (i = 1; i <= m; i++)
  {
    fin >> x >> y;
    G.AdaugaMuchieOrientata(x, y);
  }
  G.Sortare();

  //CTC

  int i, n, m, x, y;
    fin >> n >> m;
    Graf G(n);
    for(i = 1; i <= m; i++) {
        fin>>x>>y;
        G.adaugaMuchieCTC(x, y);
    }
    G.CompTareConexe();

  //Havel-Hakimi

  /*int n, i, c;
  Graf G();
  vector <int> a;
  cin >> n;
  for(i = 1; i <= n; i++) {
      cin >> c;
      a.push_back(c);
  }
  Graf :: VerifHavHak(a) ? cout << "Exista" : 
                           cout << "Nu exista";

  //APM

  int n, m, i, x, y, w;
  fin >> n >> m;
  Graf G(n);
  for (i = 1; i <= m; i++)
  {
    fin >> x >> y >> w;
    G.adaugaMuchieAPM(x, y, w);
  }
  G.Kruskall();

  //Disjoint

  int n, m, i, x, y, w;
  fin >> n >> m;
  Graf G(n);
  for (i = 1; i <= m; i++)
  {
    fin >> w >> x >> y;
    G.adaugaMuchieAPM(w, x, y);
  }
  G.Disjoint();

  //Dijkstra

  int i, n, m, x, y, w;
  fin >> n >> m;
  Graf G(n);
  for (i = 1; i <= m; i++)
  {
    fin >>x>>y>>w;
    G.adaugaMuchieDijkstra(x, y, w);
  }
  G.Dijkstra(1);

  //BellmanFord

  int i, n, m, x, y, w;
  fin >> n >> m;
  Graf G(n);
  for (i = 1; i <= m; i++)
  {
    fin >>x>>y>>w;
    G.adaugaMuchieDijkstra(x, y, w);
  }
  G.BellmanFord(1);

  //Roy-Floyd

  int n;
  fin >> n;
  Graf G(n);
  G.adaugaMuchieRoyFloyd();
  G.AfisareRoyFloyd();

  //DARB

  int i, x, y, n;
  fin >> n;
  Graf G(n);
  for (i = 1; i <= n; i++)
  {
    fin >> x >> y;
    G.AdaugaMuchieNeorientata(x, y);
  }
  fout << G.AfisareDarb();

  //Ciclu Eulerian

  int n, m, i, x, y;
  fin >> n >> m;
  Graf G(n, m);
  for (i = 0; i < m; ++i)
  {
    fin >> x >> y;
    G.adaugaMuchieEuler(x, y, i);
  }
  G.AfiseazaEuler();*/

  return 0;
}