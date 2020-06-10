/*
ID: siva.ja1
TASK: wormhole
LANG: C++
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#define IO(i, o) freopen(i, "r", stdin), freopen(o, "w", stdout)

using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

int n, cnt;
map<int, int> mp;
pair<int, int> arr[12];

void recurse(int cur){
	if(cur < n){
		if(mp.find(cur) == mp.end()){
			for(int i = cur + 1; i < n; i++)
				if(mp.find(i) == mp.end()){
					mp[cur] = i, mp[i] = cur;
					recurse(cur + 1);
					mp.erase(cur), mp.erase(i);
				}
		}else recurse(cur + 1);
	}else{
		bool val = false;
		for(int i = 0; i < n; i++){
			bitset<12> vis;
			int vtx = i;
			while(true){
				vis[vtx] = 1;
				vtx = mp[vtx];
				pair<int, int> mn = {INT_MAX, -1};
				for(auto &j : mp)
					if(arr[j.first].second == arr[vtx].second && arr[j.first].first > arr[vtx].first)
						mn = min(mn, {arr[j.first].first, j.first});
				if(vis[mn.second]){
					val = true;
					break;
				}else if(mn.second == -1) break;
				else vtx = mn.second;
			}
		}
		cnt += val;
	}
}

int main(){
	IO("wormhole.in", "wormhole.out");
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	for(int i = 0; i < n; i++) cin >> arr[i].first >> arr[i].second;
	recurse(0);
	cout << cnt << "\n";
	return 0;
}