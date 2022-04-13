class Solution {
public:
    int Y, X;
    
    bool touchedPacific(int y, int x){
        return (y < 0 || x < 0);
    }
    
    bool touchedAtlantic(int y, int x){
        return (y >= Y || x >= X);
    }
    
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        vector<vector<int>> ret;
        Y = heights.size();
        X = heights[0].size();
        int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
        
        for(int y = 0; y < Y; y++){
            for(int x = 0; x < X; x++){
                //vector<vector<bool>> visited(Y, vector<bool>(X));
                int visited[200][200] = {0};
                
                int ocean[2] = {0};
                queue<pair<int,int>> q;
                q.push({y, x});
                visited[y][x] = true;
                
                while(!q.empty()){
                    pair<int,int> curr = q.front(); 
                    q.pop();
                    int y = curr.first, x = curr.second;
                    
                    for(int d = 0; d < 4; d++){
                        int ny = y + dy[d], nx = x + dx[d];
                        
                        if(ny < 0 || nx < 0){
                            ocean[0] = true;
                            continue;
                        }
                        if(ny >= Y || nx >= X){
                            ocean[1] = true;
                            continue;
                        }
                        
                        if(visited[ny][nx]) continue;
                        
                        if(ocean[0] && ocean[1]) break;
                                                
                        if(heights[ny][nx] <= heights[y][x]){
                            q.push({ny, nx});
                            visited[ny][nx] = true;
                        }
                    }
                }
                
                if(ocean[0] && ocean[1]) ret.push_back({y, x});
            }
        }
        
        return ret;
    }
};