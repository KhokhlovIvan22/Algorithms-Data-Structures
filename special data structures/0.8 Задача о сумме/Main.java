import java.io.*;
import java.util.StringTokenizer;

public class Main {
    private static class SegmentationTree {
        private long[] tree;

        private void doBuild (int v, long[]a,int leftBorder,int rightBorder){
            if (rightBorder-leftBorder==1) {
                tree[v] = a[leftBorder];
                return;
            }
            int m = (leftBorder+rightBorder)/2;
            doBuild(2*v,a,leftBorder,m);
            doBuild(2*v+1,a,m,rightBorder);
            tree[v]=tree[2*v]+tree[2*v+1];
        }

        public SegmentationTree (int n, long[]a) {
            tree=new long[4*n];
            doBuild(1,a,0,n);
        }

        private void doAdd (int v, int x, int leftBorder, int rightBorder, int i) {
            if (rightBorder-leftBorder==1) {
                tree[v]+=x;
                return;
            }
            int m = (leftBorder+rightBorder)/2;
            if (i<m)
                doAdd(2*v,x,leftBorder,m,i);
            else
                doAdd(2*v+1,x,m,rightBorder,i);
            tree[v]=tree[2*v]+tree[2*v+1];
        }

        public void add (int x,int i, int n)
        {
            doAdd(1,x,0,n,i);
        }

        public long findSum(int v, int leftBorder,int rightBorder, int l, int r) {
            if (leftBorder==l && rightBorder==r)
                return tree[v];
            int m = (leftBorder+rightBorder)/2;
            if (r<=m)
                return findSum(2*v,leftBorder,m,l,r);
            if (l>=m)
                return findSum(2*v+1,m,rightBorder,l,r);
            return (findSum(2*v,leftBorder,m,l,m)+findSum(2*v+1,m,rightBorder,m,r));
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
        int n = Integer.parseInt(in.readLine());
        long[] a = new long[n];
        StringTokenizer st = new StringTokenizer(in.readLine());
        for (int i=0;i<n;++i)
            a[i]=Long.parseLong(st.nextToken());
        SegmentationTree tree = new SegmentationTree(n,a);
        int q = Integer.parseInt(in.readLine());
        for (int j=0;j<q;++j)
        {
            st = new StringTokenizer(in.readLine());
            if (st.nextToken().equals("Add"))
            {
                int i = Integer.parseInt(st.nextToken());
                int x = Integer.parseInt(st.nextToken());
                tree.add(x,i,n);
            }
            else
            {
                int l = Integer.parseInt(st.nextToken());
                int r = Integer.parseInt(st.nextToken());
                out.println(tree.findSum(1,0,n,l,r));
            }
        }
        out.flush();
    }
}
