class SnapshotArray {
    vector<map<int, int>> arr; // {index, {snap_id, val}}
    int g_snap_id;
public:
    SnapshotArray(int length) {
        arr.resize(length);
        for (int i = 0; i < length; i++)
            arr[i][-1] = 0;

        g_snap_id = -1;
    }
    
    void set(int index, int val) {
        auto& snaps = arr[index];
        if (snaps.rbegin()->second == val) {
            return;
        }

        arr[index][g_snap_id + 1] = val; 
    }
    
    int snap() {
        g_snap_id++;
        return g_snap_id;
    }
    
    int get(int index, int snap_id) {
        auto& snaps = arr[index];
        auto& prev_or_curr_snap = --snaps.upper_bound(snap_id);

        return prev_or_curr_snap->second;
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */