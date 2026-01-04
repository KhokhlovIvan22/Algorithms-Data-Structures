import java.io.*;
import java.util.*;

public class Main {
    public static int R, C;
    public static ArrayList<Integer>[] adjacency;
    public static int[] A, B, answer;
    public static boolean[] visited, usedEdge;
    
    public static ArrayList<Integer> componentNodes = new ArrayList<>();
    public static int cycleStart = -1;

    public static void dfs1(int v, int incomingEdge)
    {
        visited[v] = true;
        componentNodes.add(v);
        for (int col : adjacency[v])
        {
            if (col == incomingEdge)
                continue;
            int u;
            if (A[col] == v)
                u = B[col];
            else u = A[col];
            if (visited[u])
            {
                if (cycleStart == -1)
                    cycleStart = u;
            }
            else
                dfs1(u, col);
        }
    }

    public static void dfs2 (int v)
    {
        visited[v] = true;
        for (int col : adjacency[v])
        {
            if (usedEdge[col])
                continue;
            usedEdge[col] = true;
            int u;
            if (A[col] == v)
                u = B[col];
            else
                u = A[col];
            if (visited[u])
                answer[col] = u;
            else
            {
                answer[col] = u;
                dfs2(u);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("input.txt"));
        PrintWriter out = new PrintWriter(new FileWriter("output.txt"));
        StringTokenizer st = new StringTokenizer(br.readLine());
        R = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        adjacency = new ArrayList[R];
        for (int i = 0; i < R; ++i)
            adjacency[i] = new ArrayList<>();
        A = new int[C];
        B = new int[C];
        answer = new int[C];
        visited = new boolean[R];
        usedEdge = new boolean[C];
        for (int i = 0; i < C; ++i)
        {
            st = new StringTokenizer(br.readLine());
            int u = Integer.parseInt(st.nextToken()) - 1;
            int v = Integer.parseInt(st.nextToken()) - 1;
            A[i] = u;
            B[i] = v;
            adjacency[u].add(i);
            adjacency[v].add(i);
            answer[i] = -1;
        }
        for (int i = 0; i < R; ++i)
        {
            if (!visited[i])
            {
                componentNodes.clear();
                cycleStart = -1;
                dfs1(i, -1);
                int totalDegree = 0;
                for (int node : componentNodes)
                    totalDegree += adjacency[node].size();
                if (totalDegree / 2 < componentNodes.size())
                {
                    out.print("No");
                    out.close();
                    return;
                }
                for (int node : componentNodes)
                    visited[node] = false;
                if (cycleStart != -1)
                    dfs2(cycleStart);
                else
                    dfs2(i);
            }
        }
        for (int i = 0; i < C; ++i)
        {
            if (answer[i] == -1)
                answer[i] = A[i];
            out.print(answer[i] + 1 + " ");
        }
        out.close();
    }
}
