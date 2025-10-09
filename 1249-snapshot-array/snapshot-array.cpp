class SnapshotArray {
	int g_snap_id;
	vector<map<int, int>> history;
public:
	SnapshotArray(int length) {
		g_snap_id = 0;
		history.resize(length);
	}
	void set(int index, int val) {
		history[index][g_snap_id] = val;
	}
	int snap() {
		return (++g_snap_id) - 1;
	}
	int get(int index, int snap_id) {
		if (snap_id < 0 || snap_id >= g_snap_id) return -1;
		auto it = history[index].upper_bound(snap_id);
		if (it == history[index].begin()) return 0;
		return (--it)->second;
	}
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */