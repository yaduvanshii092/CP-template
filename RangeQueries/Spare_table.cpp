//---------------------SPARE TABLE----------------------
   //Use it for min max gcd idempotant function and rage sum problems  

template<typename Node>
struct SparseTable {
	vector<vector<Node>> table;
	vector<int> logValues;
	int n;
	int maxLog;
	vector<int> a;
	SparseTable(int n1, vector<int> &arr) {
		n = n1;
		a = arr;
		table.resize(n);
		logValues.resize(n + 1);
		maxLog = log2(n);
		logValues[1] = 0;
		for (int i = 2; i <= n; i++) {
			logValues[i] = logValues[i / 2] + 1;
		}
		for (int i = 0; i < n; i++) {
			table[i].resize(maxLog + 1);
			fill(table[i].begin(),table[i].end(), Node());
		}
		build();
	}
	void build() {
		for (int i = 0; i < n; i++) {
			table[i][0] = Node(a[i]); // Base Case
		}
		for (int i = 1; i <= maxLog; i++) {
			for (int j = 0; (j + (1 << i)) <= n; j++) {
				table[j][i].merge(table[j][i - 1], table[j + (1 << (i - 1))][i - 1]);
			}
		}
	}
	Node queryNormal(int left, int right) {
		Node ans = Node();
		for (int j = logValues[right - left + 1]; j >= 0; j--) {
			if ((1 << j) <= right - left + 1) {
				ans.merge(ans, table[left][j]);
				left += (1 << j);
			}
		}
		return ans;
	}
	Node queryIdempotent(int left, int right) {
		int j = logValues[right - left + 1];
		Node ans = Node();
		ans.merge(table[left][j], table[right - (1 << j) + 1][j]);
		return ans;
	}
};
struct Node1 {
	int val; // store more info if required
	Node1() { // Identity Element
		val = 0;
	}
	Node1(int v) {
		val = v;
	}
    // Modify Here as according to required answer what you want sum,gcd,max,min
	void merge(Node1 &l, Node1 &r) {
		val = l.val + r.val;
	}
};

void solve()
{
    // n is size of vector arr
    vector<int> arr;    int n,q;
    SparseTable<Node1> g(n,arr);
    while (q--)
    {
        int l,r;    cin>>l>>r;  l--; r--;   // 0 based Indexing
    }
}

// Practice
// https://codeforces.com/contest/1562/problem/D1