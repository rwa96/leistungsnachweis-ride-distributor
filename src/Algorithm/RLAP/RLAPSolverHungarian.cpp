#include <algorithm>
#include <limits>
#include "RLAPSolverHungarian.hpp"

#define MAX_DIM(m) std::max(m.getDims()[0], m.getDims()[1])

RLAPSolverHungarian::RLAPSolverHungarian(const Tensor<int>& mat, const unsigned rows,
        const unsigned cols, const int maxCost):
    rows(rows),
    cols(cols),
    size(MAX_DIM(mat)),
    costMat({MAX_DIM(mat), MAX_DIM(mat)}, 0),
assignMat({MAX_DIM(mat), MAX_DIM(mat)}, 0) {
    for(unsigned row = 0; row < rows; ++row) {
        for(unsigned col = 0; col < cols; ++col) {
            costMat(row, col) = maxCost - mat(row, col);
        }
    }

    if(rows != cols) {
        unsigned row, col;

        if(rows > cols)
        {row = 0; col = cols;}
        else
        {row = rows; col = 0;}

        for(; row < size; ++row) {
            for(; col < size; ++col) {
                costMat(row, col) = maxCost;
            }
        }
    }
}

void RLAPSolverHungarian::solve(Tensor<int>& assignments) {
    Tensor<int> colVert({size}), rowVert({size}), unchosenRow({size}), parentRow({size}),
           rowDec({size}), colInc({size}), slackRow({size}), slack({size});

    for(unsigned i = 0; i < size; ++i) {
        colVert(i) = 0;
        rowVert(i) = 0;
        unchosenRow(i) = 0;
        parentRow(i) = 0;
        rowDec(i) = 0;
        colInc(i) = 0;
        slackRow(i) = 0;
        slack(i) = 0;
    }

    for(unsigned col = 0; col < size; ++col) {

    }
}/*
  // Begin subtract column minima in order to start with lots of zeroes 12
	for (l=0;l<n;l++)
	{
		s = m_costmatrix[0][l];

		for (k=1;k<m;k++)
		{
			if (m_costmatrix[k][l] < s)
			{
				s=m_costmatrix[k][l];
			}
			cost += s;
		}

		if (s!=0)
		{
			for (k=0;k<m;k++)
			{
				m_costmatrix[k][l]-=s;
			}
		}

		//pre-initialize state 16
		row_vertex[l]= -1;
		parent_row[l]= -1;
		col_inc[l]=0;
		slack[l]=INF;
	}
  // End subtract column minima in order to start with lots of zeroes 12

  // Begin initial state 16
	t=0;

	for (k=0;k<m;k++)
	{
		bool row_done = false;
		s=m_costmatrix[k][0];

		for (l=0;l<n;l++)
		{

			if(l > 0)
			{
				if (m_costmatrix[k][l] < s)
				{
					s = m_costmatrix[k][l];
				}
				row_dec[k]=s;
			}

			if (s == m_costmatrix[k][l] && row_vertex[l]<0)
				{
					col_vertex[k]=l;
					row_vertex[l]=k;

					if (verbose)
					{
						fprintf(stderr, "matching col %d==row %d\n",l,k);
					}
					row_done = true;
					break;
				}
		}

		if(!row_done)
		{
			col_vertex[k]= -1;

			if (verbose)
			{
				fprintf(stderr, "node %d: unmatched row %d\n",t,k);
			}

			unchosen_row[t++]=k;
		}

	}
  // End initial state 16

	bool checked = false;

  // Begin Hungarian algorithm 18

	//is matching already complete?
	if (t == 0)
	{
		checked = check_solution(row_dec, col_inc, col_vertex);
		if (checked)
		{
			//finish assignment, wrap up and done.
			bool assign = assign_solution(row_dec, col_inc, col_vertex);
			return true;
		}
		else
		{
			if(verbose)
			{
				fprintf(stderr, "Could not solve. Error.\n");
			}
			return false;
		}
	}

	unmatched=t;


	while (1)
	{
		if (verbose)
		{
			fprintf(stderr, "Matched %d rows.\n",m-t);
		}
		q=0;
		bool try_matching;
		while (1)
		{
			while (q<t)
			{
			// Begin explore node q of the forest 19

				k=unchosen_row[q];
				s=row_dec[k];
				for (l=0;l<n;l++)
				{
					if (slack[l])
					{
						int del;
						del=m_costmatrix[k][l]-s+col_inc[l];
						if (del<slack[l])
						{
							if (del==0)
							{
								if (row_vertex[l]<0)
								{
									goto breakthru;
								}
								slack[l]=0;
								parent_row[l]=k;
								if (verbose)
									fprintf(stderr, "node %d: row %d==col %d--row %d\n",
									t,row_vertex[l],l,k);
									unchosen_row[t++]=row_vertex[l];
							}
							else
							{
								slack[l]=del;
								slack_row[l]=k;
							}
						}
					}
				}
			// End explore node q of the forest 19
				q++;
			}

	  // Begin introduce a new zero into the matrix 21
		s=INF;
		for (l=0;l<n;l++)
		{
			if (slack[l] && slack[l]<s)
			{
				s=slack[l];
			}
		}
		for (q=0;q<t;q++)
		{
			row_dec[unchosen_row[q]]+=s;
		}
		for (l=0;l<n;l++)
		{
			//check slack
			if (slack[l])
			{
				slack[l]-=s;
				if (slack[l]==0)
				{
					// Begin look at a new zero 22
					k=slack_row[l];
					if (verbose)
					{
						fprintf(stderr,
						"Decreasing uncovered elements by %d produces zero at [%d,%d]\n",
						s,k,l);
					}
					if (row_vertex[l]<0)
					{
						for (j=l+1;j<n;j++)
							if (slack[j]==0)
							{
								col_inc[j]+=s;
							}

						goto breakthru;
					}
					else
					{
						parent_row[l]=k;
						if (verbose)
						{
							fprintf(stderr, "node %d: row %d==col %d--row %d\n",t,row_vertex[l],l,k);
							unchosen_row[t++]=row_vertex[l];
						}
					}
		// End look at a new zero 22
				}
			}
			else
			{
				col_inc[l]+=s;
			}
		}
	// End introduce a new zero into the matrix 21
	}

    breakthru:
      // Begin update the matching 20
		if (verbose)
		{
			fprintf(stderr, "Breakthrough at node %d of %d!\n",q,t);
		}
		while (1)
		{
			j=col_vertex[k];
			col_vertex[k]=l;
			row_vertex[l]=k;
			if (verbose)
			{
				fprintf(stderr, "rematching col %d==row %d\n",l,k);
			}
			if (j<0)
			{
				break;
			}
			k=parent_row[j];
			l=j;
		}
		// End update the matching 20
		if (--unmatched == 0)
		{
			checked = check_solution(row_dec, col_inc, col_vertex);
			if (checked)
			{
				//finish assignment, wrap up and done.
				bool assign = assign_solution(row_dec, col_inc, col_vertex);
				return true;
			}
			else
			{
				if(verbose)
				{
					fprintf(stderr, "Could not solve. Error.\n");
				}
				return false;
			}
		}

		// Begin get ready for another stage 17
			t=0;
			for (l=0;l<n;l++)
			{
				parent_row[l]= -1;
				slack[l]=INF;
			}
			for (k=0;k<m;k++)
			{
				if (col_vertex[k]<0)
				{
					if (verbose)
						fprintf(stderr, "node %d: unmatched row %d\n",t,k);
					unchosen_row[t++]=k;
				}
			}
		// End get ready for another stage 17
	}// back to while loop
}*/
