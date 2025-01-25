# README

## Student Information
- **Name:** R. Dilukshi  
- **Section Numbers:** 23000333 & 2023/CS/033  
- **Email Address:** dilurusi@gmail.com  

## Code Testing Environment
- **Tested on Linux:** Yes

## How to Execute the Program
1. Place the input file named `graph.txt` in the same directory as the program.
2. Compile the program using the following command:
   ```bash
   gcc -o graph_bfs bfs.c
   ```
3. Run the program using the command:
   ```bash
   ./graph_bfs
   ```

## Special Notes
- The program reads a graph from `graph.txt` and performs BFS traversal starting from the node with the highest number of connections.
- A function is used to dynamically choose the start node based on the graph structure; the first element in the input is not always the starting node for every problem.
- The adjacency matrix representation is used for the graph, and the program supports both directed and undirected graphs.
- The output includes the BFS traversal path, total weight of edges, and any unreachable nodes.
- Ensure the `graph.txt` file is formatted correctly with the number of nodes, type of graph (`directed` or `undirected`), and edges with weights.

