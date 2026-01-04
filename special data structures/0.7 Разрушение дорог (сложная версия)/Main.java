import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
    static class DisjointSetUnion {
        private int[] parent;
        private int count;

        public DisjointSetUnion(int n) {
            parent = new int[n + 1];
            Arrays.fill(parent, -1);
            count = n;
        }

        public int findSet(int x) {
            if (parent[x] < 0)
                return x;
            else
                parent[x] = findSet(parent[x]);
            return parent[x];
        }

        public void union(int x, int y) {
            int set_x = findSet(x);
            int set_y = findSet(y);
            if (set_x == set_y) return;
            else {
                if (parent[set_x] > parent[set_y]) {
                    int tmp = set_x;
                    set_x = set_y;
                    set_y = tmp;
                }
                parent[set_x] += parent[set_y];
                parent[set_y] = set_x;
                count--;
            }
        }

        public int countSets() {
            return count;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("input.txt"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        int q = Integer.parseInt(st.nextToken());
        int[] u = new int[m + 1];
        int[] v = new int[m + 1];
        for (int i = 1; i <= m; ++i) {
            st = new StringTokenizer(br.readLine());
            u[i] = Integer.parseInt(st.nextToken());
            v[i] = Integer.parseInt(st.nextToken());
        }
        int[] destroyed = new int[q + 1];
        boolean[] isDestroyed = new boolean[m+1];
        for (int i = 1; i <= q; ++i) {
            st = new StringTokenizer(br.readLine());
            destroyed[i] = Integer.parseInt(st.nextToken());
            isDestroyed[destroyed[i]]=true;
        }
        br.close();
        DisjointSetUnion roads = new DisjointSetUnion(n);
        for (int i = 1; i <= m; i++)
            if (!isDestroyed[i])
                roads.union(u[i], v[i]);
        StringBuilder sb = new StringBuilder();
        for (int i = q; i >= 1; --i)
        {
        if (roads.countSets() > 1)
            sb.append(0);
        else
            sb.append(1);
        roads.union(u[destroyed[i]], v[destroyed[i]]);
        }
        sb.reverse();
        BufferedWriter bw = new BufferedWriter(new FileWriter("output.txt"));
        bw.write(sb.toString());
        bw.close();
    }
}
