class Solution {
    ArrayList<String> longestWords(String[] dictionary) {
        ArrayList<String> res = new ArrayList<String>();
        for (String str : dictionary) {
            if (res.isEmpty() || res.get(0).length() < str.length()) {
                res.clear();
                res.add(str);
            } else if (res.get(0).length() == str.length()) {
                res.add(str);
            }
        }
        return res;
    }
};
