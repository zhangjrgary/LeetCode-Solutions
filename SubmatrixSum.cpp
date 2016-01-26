//Naive solution is O(n^4). But on 1 certain dimension, naive O(n^2) can be O(n) by this well-known equation: sum[i..j] = sum[0..j] - sum[0..i]. And pls take care of several corner cases.
//class Solution {
public:
    /**
     * @param matrix an integer matrix
     * @return the coordinate of the left-up and right-down number
     */
    vector<vector<int>> submatrixSum(vector<vector<int>>& m) {

        int h = m.size();
        if(!h) return {};
        int w = m[0].size();
        if(!w) return {};

        // Get accumulate sum by columns
        vector<vector<int>> cols(h, vector<int>(w, 0));        
        for(int i = 0; i < w; i ++)
        {
            unordered_map<int, int> rec; // sum-inx
            for(int j = 0; j < h; j ++)
            {
                if(m[j][i] == 0)
                {
                    return {{i, j},{i, j}};
                }

                cols[j][i] = (j ? cols[j - 1][i] : 0) + m[j][i];
                if (!cols[j][i])
                {
                    return {{0, i}, {j, i}};
                }
                else if(rec.find(cols[j][i]) != rec.end())
                {
                    return {{rec[cols[j][i]] + 1, i}, {j, i}};
                }
                rec[cols[j][i]] = j;
            }
        }

        //  horizontal case
        for(int i = 0; i < h; i ++)
        for(int j = i; j < h; j ++)
        {
            vector<int> hsum(w, 0);
            for(int x = 0; x < w; x ++)
            {
                int prev = ((i == 0) ? 0 : cols[i - 1][x]);
                hsum[x] = cols[j][x] - prev;
            }
            // 
            vector<int> asum(w, 0);
            unordered_map<int, int> rec; // sum-inx
            for(int x = 0; x < w; x ++)
            {
                int nsum = (x ? asum[x - 1] : 0) + hsum[x];
                if (!nsum)
                {
                    return {{i + 1, 0}, {j, x}};
                }
                else if(rec.find(nsum) != rec.end())
                {
                    return {{i, rec[nsum] + 1}, {j, x}};
                }
                rec[nsum] = x;
                asum[x] = nsum;
            }
        }

        return {};
    }
};