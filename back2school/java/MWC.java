import java.util.*;

public class MWC {
    int[] degree;   // degree of vertices
    int[] weight;   // weight of vertices
    int[][] A;      // 0/1 adjacency matrix
    int n;          // n vertices
    long nodes;     // number of decisions
    long whenFound; // node count when incumbent found
    long timeLimit; // milliseconds
    long cpuTime;   // milliseconds
    long maxWeight; // weight of max clique
    int style;      // used to flavor algorithm
    int[] solution; // as it says
    //Vertex[] V;     // for ordering vertices
    boolean trace;  // for a trace

    MWC (int n,int[][] A,int[] degree,int[] weight,int style) {
	this.n = n;
	this.A = A;
	this.degree = degree;
	this.weight = weight;
	nodes = whenFound = maxWeight = 0;
	cpuTime = timeLimit = -1;
	trace = false;
	this.style = style;
	solution = new int[n];
	//V = new Vertex[n];
	//for (int i=0;i<n;i++) V[i] = new Vertex(i,degree[i],weight[i]);
    }

    void search(){
	cpuTime              = System.currentTimeMillis();
	nodes                = 0;
	ArrayList<Integer> C = new ArrayList<Integer>();
	ArrayList<Integer> P = new ArrayList<Integer>(n);
	for (int i=n-1;i>=0;i--) P.add(i); // reverse order from colourists
	expand(C,P,getWeight(C),getWeight(P));
	if (trace) System.out.println(nodes +" "+ maxWeight);
    }

    void expand(ArrayList<Integer> C,ArrayList<Integer> P,long cWeight,long pWeight){
	if (timeLimit > 0 && System.currentTimeMillis() - cpuTime >= timeLimit) return;
	nodes++;
	int m = P.size();
	for (int i=m-1;i>=0;i--){
	    if (cWeight + pWeight <= maxWeight) return;
	    int v = P.get(i);
	    C.add(v);
	    ArrayList<Integer> newP = new ArrayList<Integer>();
	    long newPWeight = 0;
	    for (int w : P) 
		if (A[v][w] == 1){
		    newP.add(w); 
		    newPWeight = newPWeight + weight[w];
		}
	    if (cWeight + weight[v] > maxWeight) saveSolution(C);
	    if (!newP.isEmpty()) expand(C,newP,cWeight+weight[v],newPWeight);
	    C.remove((Integer)v);
	    P.remove((Integer)v);
	    pWeight = pWeight - weight[v];
	}
    }

    long getWeight(ArrayList<Integer> v){
	long totalWeight = 0;
	for (int i : v) totalWeight = totalWeight + weight[i];
	return totalWeight;
    }


    void saveSolution(ArrayList<Integer> C){
	Arrays.fill(solution,0);
	for (int i : C) solution[i] = 1;
	maxWeight = getWeight(C);
	whenFound = nodes;
	if (trace) System.out.println(nodes +" "+ maxWeight);
    }
}