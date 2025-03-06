class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<vector<string>> lines(1);
        int width = 0;
        for (auto& word : words) {
            width += word.size();

            if (width > maxWidth) {
                lines.push_back(vector<string>(0));
                width = word.size();
            }

            lines.back().push_back(word);
            width += 1;
        }

        return addSpace(lines, maxWidth);
    }
    vector<string> addSpace(vector<vector<string>>& lines, int maxWidth) {
        vector<string> ret;
        auto lineWidth = [&](vector<string>& line) {
            int size = 0;
            for (auto& word : line)
                size += word.size();
            return size;
        };

        for (int i = 0; i < lines.size(); i++) {
            auto line = lines[i];
            int numWords = line.size();
            int numSpace = max(numWords - 1, 1);
            int spaceWidth = maxWidth - lineWidth(line);

            int eachSpace = spaceWidth / numSpace;
            int extraSpace = spaceWidth % numSpace;

            if (i == lines.size() - 1) {
                eachSpace = 1;
                extraSpace = 0;
            }

            string justified;
            for (int j = 0; j < line.size(); j++) {
                auto& word = line[j];
                justified += word;

                if (j < line.size() - 1 ||
                    (line.size() == 1 && i != lines.size() - 1)) {
                    justified += string(eachSpace, ' ');

                    if (extraSpace > 0) {
                        justified += " ";
                        extraSpace--;
                    }
                }
            }

            if (i == lines.size() - 1) {
                justified += string(maxWidth - justified.size(), ' ');
            }

            ret.push_back(justified);
        }

        return ret;
    }
};