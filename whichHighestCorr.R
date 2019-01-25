

whichHightestCorr <- function(m1, m2, largest_ncol) {

# whichHighestCorr(m1, m2)
#
#   inputs m1 and m2 are both matrices
#   a function that determines which connections has the 
#      highest correlation
#
  #apply(m1, 2, function(col) col + 1)#
  
length_column <- ncol(m2)
vec <- rep(NA, largest_ncol)
for (j in 1:length_column)
  {
  result = apply(m1, 2, function(col) cor(col,m2[,j]))
  vec[j] = which.max(result)
  }
return(vec)
}

 

              



