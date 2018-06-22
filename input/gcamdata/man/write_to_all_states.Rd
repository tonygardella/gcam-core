% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/module-helpers.R
\name{write_to_all_states}
\alias{write_to_all_states}
\title{write_to_all_states}
\usage{
write_to_all_states(data, names)
}
\arguments{
\item{data}{Base tibble to start from}

\item{names}{Character vector indicating the column names of the returned tibble}
}
\value{
Tibble with data written out to all USA states
}
\description{
write out data to all states
}
\note{
Used for USA national data by GCAM region, which is repeated for each US state
}