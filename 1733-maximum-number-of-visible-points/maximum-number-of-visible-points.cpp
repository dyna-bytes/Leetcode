class Solution {
#define _USE_MATH_DEFINES
double pi = M_PI;
public:
    double getRad(int dy, int dx) {
        double rad = atan2(dy, dx);
        if (rad < 0) rad += 2*pi;
        return rad;
    }
    
    double degToRad(int deg) {
        return deg * 2 * pi / 360;
    }

    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        double radian_window = degToRad(angle);
        vector<double> angles;
        int same_with_origin = 0;

        for (auto& p: points) {
            if (p[0] == location[0] && p[1] == location[1]) {
                same_with_origin++;
                continue;
            }

            int dx = p[0] - location[0];
            int dy = p[1] - location[1];
            double rad = getRad(dy, dx);

            angles.push_back(rad);
            angles.push_back(rad + 2*pi);
        }

        sort(angles.begin(), angles.end());

        int max_points = 0;
        for (int s = 0, e = 0; s < angles.size(); s++) {
            double window = angles[s] + radian_window;
            while (e < angles.size() && angles[e] <= window) 
                e++;

            max_points = max(max_points, e - s);
        }
        return max_points + same_with_origin;
    }
};
