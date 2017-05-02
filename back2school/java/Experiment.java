import java.util.*;
import java.io.*;

public class Experiment {

    static int[] degree;   // degree of vertices
    static int[] weight;   // weight of vertices
    static int[][] A;      // 0/1 adjacency matrix
    static int n, minWeight, maxWeight;

    static void readGraph(String fname) throws IOException {
	Scanner sc = new Scanner(new File(fname));
	String s   = "";
	while (sc.hasNext() && !s.equals("p")) s = sc.next();
	sc.next();
	n          = sc.nextInt();
	int m      = sc.nextInt();
	minWeight  = 0;
	maxWeight  = 0;
	degree     = new int[n];
	weight     = new int[n];
	A          = new int[n][n];

	// read vertex weights
	for (int i=0;i<n;i++){
	    s = sc.next(); // skip n
	    int v = sc.nextInt() - 1; // vertex id
	    weight[v] = sc.nextInt();
	}

	// read edges
	while(sc.hasNext()){
	    s     = sc.next(); // skip "edge"
	    int u = sc.nextInt() - 1;
	    int v = sc.nextInt() - 1;
	    A[u][v] = A[v][u] = 1;
	    degree[u]++;
	    degree[v]++;
	}
	sc.close();
    }

    public static void main(String[] args)  throws IOException {
	readGraph(args[0]);
	MWC mwc  = new MWC(n,A,degree,weight,0);
	long cpuTime = System.currentTimeMillis();
	mwc.search();
	cpuTime = System.currentTimeMillis() - cpuTime;
	if (!mwc.trace){
	    System.out.println(mwc.maxWeight +" "+ mwc.nodes +" "+ cpuTime);
	    for (int i=0;i<mwc.n;i++) if (mwc.solution[i] == 1) System.out.print((i+1) +" ");
	    System.out.println();
	}
    }
}