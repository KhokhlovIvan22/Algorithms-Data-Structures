import java.util.*;
import java.util.Arrays;
import java.util.ArrayList;

public class Main {
    static int dp[][];
    static int A[];
    static int B[];
    static ArrayList<Integer> A_ind=new ArrayList<Integer>();
    static ArrayList<Integer> B_ind=new ArrayList<Integer>();

    public static int lcs (int n, int k) {
        if (n==0 || k==0) return 0;
        if (dp[n][k]!=-1) return dp[n][k];
        if (A[n]==B[k])
            dp[n][k] = lcs(n-1,k-1)+1;
        else
            dp[n][k] = Math.max(lcs(n-1,k),lcs(n,k-1));
        return dp[n][k];
    }

    public static void indexes (int n) {
        int i=n;
        int j=n;
        while (i>0 && j>0)
        {
            if (A[i]==B[j]) {
                A_ind.add(i);
                B_ind.add(j);
                i--;
                j--;
            }
            else if (dp[i-1][j]>=dp[i][j-1])
                i--;
            else
                j--;
        }
    }

    public static void main(String[] args) {
        Scanner in = new Scanner (System.in);
        int n = in.nextInt();
        dp = new int[n+1][n+1];
        for (int[]row:dp)
            Arrays.fill(row,-1);
        A = new int[n+1];
        for (int i=1;i<=n;++i)
            A[i]=in.nextInt();
        B = new int[n+1];
        for (int i=1;i<=n;++i)
            B[i]=in.nextInt();
        System.out.println(lcs(n,n));
        indexes(n);
        Collections.reverse(A_ind);
        Collections.reverse(B_ind);
        for (int curInd: A_ind)
            System.out.print(curInd-1 + " ");
        System.out.println();
        for (int curInd: B_ind)
            System.out.print(curInd-1 + " ");
    }
}
