set.seed(123)

var_ob <- function(x) {
  N <- length(x)
  m <- mean(x)
  sum((x - m)^2) / N
}

fn_ecdf <- function(x) {
  ecdf(x)(0)
}

n <- c(10, 100, 1000)

x <- list(
  norm = sapply(n, rnorm, mean = 0, sd = 1),
  exp = sapply(n, rexp, rate = 2)
)

ref_vals <- list(
  norm = c(mean = 0, var = 1),
  exp = c(mean = 0.5, var = 0.25)
)

for (i in names(x)) {
  current_list <- x[[i]]
  current_refs <- ref_vals[[i]]

  oczekiwana <- sapply(current_list, mean)
  wariancja_obciazona <- sapply(current_list, var_ob)
  wariancja <- sapply(current_list, var)
  dystrybuanta <- sapply(current_list, ecdf)

  print(i)
  print(data.frame(
    n = c(n, "ref"),
    oczekiwana = c(oczekiwana, current_refs["mean"]),
    wariancja_obciazona = c(wariancja_obciazona, current_refs["var"]),
    wariancja = c(wariancja, current_refs["var"])
  ))
}
