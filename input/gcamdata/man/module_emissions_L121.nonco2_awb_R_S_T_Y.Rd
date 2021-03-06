% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/zchunk_L121.nonco2_awb_R_S_T_Y.R
\name{module_emissions_L121.nonco2_awb_R_S_T_Y}
\alias{module_emissions_L121.nonco2_awb_R_S_T_Y}
\title{module_emissions_L121.nonco2_awb_R_S_T_Y}
\usage{
module_emissions_L121.nonco2_awb_R_S_T_Y(command, ...)
}
\arguments{
\item{command}{API command to execute}

\item{...}{other optional parameters, depending on command}
}
\value{
Depends on \code{command}: either a vector of required inputs,
a vector of output names, or (if \code{command} is "MAKE") all
the generated outputs: \code{L121.AWBshare_R_C_Y_GLU}, \code{L121.nonco2_tg_R_awb_C_Y_GLU}. The corresponding file in the
original data system was \code{L121.nonco2_awb_R_S_T_Y.R} (emissions level1).
}
\description{
Calculates 1) share of agricultural waste burning emissions by crop and land use unit, and 2) a default set of agricultural waste burning emissions at this same level.
}
\details{
The share of AWB emissions within each region is calculated on the basis of excess dry biomass estimated from production, harvest index, and water content. EDGAR AWB emissions are then used to estimate emissions for each GCAM production technology
}
\author{
KD May 2017
}
