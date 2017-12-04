// Create the matrice of the character


int* build_matrix(size_t dimension) {
  int *matrix;
  matrix = malloc(dimension * sizeof(int *));
  for (size_t i = 0; i < dimension; ++i)
    matrix[i] = malloc(dimension * sizeof(int));
  return matrix;
}

int[] CreateMat(SDL_Surface *picture,int beginline,
int endline,int begincolumn, int endcolumn)
{
  int nbline = endline + 1 - beginline;
  int nbcolumn = endcolumn + 1 - begincolumn;
  int mat[nbcolumn + nbline * nbcolumn];
  Uint8 r, g , b;
  Uint32 pixel;
  for (int i = begincolumn; i <= endcolumn; i+)
  {
    for (int j = beginline; j <= endline; j++)
    {
      pixel = getpixel(picture, i, j);
      SDL_GetRGB(pixel, picture->format, &r, &g, &b);
      if (g == 255)
        mat[i + j * column] = 1;  // coordonnées à vérifier
      else
        mat[i + j * column] = 0;
    }
  }
  return mat;
}

int[][] CreateMat(SDL_Surface *picture,int beginline,
int endline,int begincolumn, int endcolumn)
{

  int nbline = endline + 1 - beginline;
  int nbcolumn = endcolumn + 1 - begincolumn;
  int mat[nbcolumn][nbline];
  Uint8 r, g , b;
  Uint32 pixel;
  for (int i = begincolumn; i <= endcolumn; i++)
  {
    for (int j = beginline; j <= endline; j++)
    {
      pixel = getpixel(picture, i, j);
      SDL_GetRGB(pixel, picture->format, &r, &g, &b);
      if (g == 255)
        mat[i][j];  // coordonnées à vérifier
      else
        mat[i][j] = 0;
    }
  }
  return mat;
}