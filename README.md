# AI Tech Stack Recommender Engine in C++

A custom C++ implementation of a Content-Based Recommendation System using Cosine Similarity and Vector Mapping. Built for Project 3 of the DecodeLabs AI Internship.

## Key Features
- **Vector Space Mapping:** Maps qualitative user preferences and job specifications into high-dimensional numerical vectors.
- **Cosine Similarity Engine:** Calculates angular alignment $\cos(\theta) = \frac{A \cdot B}{\Vert{}A\Vert{} \Vert{}B\Vert{}}$ to determine precise profile matching.
- **Top-N Ranking Pipeline:** Ingests user state, scores items against dataset vectors, sorts scores, and outputs truncated top recommendations.

## How to Run

### Prerequisites
- GCC / G++ Compiler

### Build & Execution
1. Compile the source code:
   ```bash
   g++ recommender.cpp -o recommender
