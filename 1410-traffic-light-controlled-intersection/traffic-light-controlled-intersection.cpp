#define debug(x) cout << #x << " is " << x << endl;

class TrafficLight {
    mutex m;
    bool passA;
public:
    TrafficLight() {
        passA = true;
    }

    bool isRoadA(int roadId) {
        return roadId == 1;
    }

    void carArrived(
        int carId,                   // ID of the car
        int roadId,                  // ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
        int direction,               // Direction of the car
        function<void()> turnGreen,  // Use turnGreen() to turn light to green on current road
        function<void()> crossCar    // Use crossCar() to make car cross the intersection
    ) {
        m.lock();
        if (isRoadA(roadId) != passA) {
            turnGreen();
            passA =! passA;
        }
        crossCar();
        m.unlock();
    }
};