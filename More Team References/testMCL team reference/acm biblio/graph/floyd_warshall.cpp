for (int k = 0; k < V; ++k)
	for (int i = 0; i < V; ++i)
		if (c[i][k] < oo)
			for (int j = 0, w; j < V; ++j)
				if ((w = c[i][k] + c[k][j]) < c[i][j])
					c[i][j] = w;