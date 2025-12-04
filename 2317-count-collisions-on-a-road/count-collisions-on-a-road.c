int countCollisions(char* directions) {
    int n = strlen(directions);
    const int MAX_SIZE = 1e5 + 1;
    int st[MAX_SIZE];
    memset(st, 0, sizeof(st));
    int sp = 0;
    
    int collisions = 0;
    for (int i = 0; i < n; i++) {
        char dir = directions[i];

        if (dir == 'R') {
            st[++sp] = dir;
        } else if (dir == 'S') {
            while (sp > 0 && st[sp] == 'R') {
                st[--sp];
                collisions++;
            }

            st[++sp] = 'S';
        } else if (dir == 'L') {
            bool hit = false;
            while (sp > 0 && (st[sp] == 'R')) {
                st[--sp];
                if (!hit) collisions += 2;
                else collisions++;
                hit = true;
            } 

            if (!hit && sp > 0 && st[sp] == 'S') {
                st[--sp];
                collisions++;
                hit = true;
            }

            if (hit)
                st[++sp] = 'S';
        }
    }

    return collisions;
}