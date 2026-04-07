class Robot {
    #define debug(x) cout << #x << " is " << x << endl;

    enum directions {
        N = 0,
        W = 1,
        S = 2,
        E = 3,
    };
    
    int Y, X;
    int y, x;
    int dir;
    int k;
public:
    Robot(int width, int height) {
        X = width - 1, Y = height - 1;
        x = y = 0;
        dir = E;
        k = 0;
    }
    
    void step(int num) {
        k = (k + num) % (2*X + 2*Y);

        if (0 < k && k <= X) {
            y = 0;
            x = k;
            dir = E;
        } else if (X < k && k <= X + Y) {
            y = k - X;
            x = X;
            dir = N;
        } else if (X + Y < k && k <= 2*X + Y) {
            x = X - (k - (X + Y));
            y = Y;
            dir = W;
        } else if (2*X + Y < k && k < 2*X + 2*Y) {
            y = Y - (k - (2*X + Y));
            x = 0;
            dir = S;
        } else if (k == 0) {
            y = 0;
            x = 0;
            dir = S;
        }
    }
    
    vector<int> getPos() {
        return {x, y};
    }
    
    string getDir() {
        if (dir == N) return "North";
        else if (dir == W) return "West";
        else if (dir == S) return "South";
        else return "East";
    }
};

/**
 * Your Robot object will be instantiated and called as such:
 * Robot* obj = new Robot(width, height);
 * obj->step(num);
 * vector<int> param_2 = obj->getPos();
 * string param_3 = obj->getDir();
 */