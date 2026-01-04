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

    public static void main(String[] args) throws FileNotFoundException, IOException {
        BufferedReader br = new BufferedReader(new FileReader("input.txt"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int q = Integer.parseInt(st.nextToken());
        StringBuilder sb = new StringBuilder();
        DisjointSetUnion roads = new DisjointSetUnion(n);
        for (int i = 0; i < q; i++) {
            st = new StringTokenizer(br.readLine());
            int r1 = Integer.parseInt(st.nextToken());
            int r2 = Integer.parseInt(st.nextToken());
            roads.union(r1, r2);
            sb.append(roads.countSets()).append('\n');
        }
        br.close();
        BufferedWriter bw = new BufferedWriter(new FileWriter("output.txt"));
        bw.write(sb.toString());
        bw.close();
    }
}
