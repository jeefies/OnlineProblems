int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};

class Solution {
public:
	int m, n;
    bool exist(vector<vector<char>>& board, string word) {
		m = board.size();
		n = board[0].size();
		if (m == 0 || n == 0) return false;

		vector<vector<bool>> visited(m, vector<bool>(n));
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				if (board[i][j] == word[0]) {
					if (search(board, visited, word, i, j, 0)) {
						return true;
					}
				}
			}
		}
		return false;
    }

	bool search(vector<vector<char>>& board, vector<vector<bool>> & visited, string & word, int i, int j, int a) {
		// ok
		if (a == word.size()) return true;
		// out
		if (i < 0 || j < 0 || i >= m || j >= n) return false;
		// not match
		if (board[i][j] != word[a]) return false;
		// visited
		if (visited[i][j]) return false;

		// set visited
		visited[i][j] = true;

		bool ok = false;
		for (int x = 0; x < 4; x++)
			ok = ok || search(board, visited, word, i + di[x], j + dj[x], a + 1);

		// backtrace
		visited[i][j] = false;
		
		return ok;
	}
};
