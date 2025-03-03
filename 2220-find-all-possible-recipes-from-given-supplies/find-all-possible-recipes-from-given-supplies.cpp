class Solution {
public:
    unordered_map<string, int> visited;
    unordered_set<string> supplies_set;

    bool dfs(string curr_recipe, vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
        visited[curr_recipe] = 1;
        int curr_idx = distance(recipes.begin(), find(recipes.begin(), recipes.end(), curr_recipe));

        int ing_cnt = 0;
        for (string& ing: ingredients[curr_idx]) {
            if (supplies_set.count(ing)) {
                ing_cnt++;
                continue;
            }
            if (find(recipes.begin(), recipes.end(), ing) != recipes.end()) {
                if (visited[ing]) { 
                    if (visited[ing] == 2) ing_cnt++;
                    continue;
                }
                if (dfs(ing, recipes, ingredients, supplies))
                    ing_cnt++;
            }
        }

        if (ing_cnt == ingredients[curr_idx].size()) {
            visited[curr_recipe] = 2;
            return true;
        }
        return false;
    }

    vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
      copy(supplies.begin(), supplies.end(), inserter(supplies_set, supplies_set.end()));
        vector<string> possible;

        for (auto recipe: recipes) {
            if (dfs(recipe, recipes, ingredients, supplies))
                possible.push_back(recipe);
        }
        return possible;
    }
};