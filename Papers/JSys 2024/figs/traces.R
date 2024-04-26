library(ggplot2)
library(grid)
library(gridExtra)
library(signal)




plot_trace <- function(column, data, row, axis_element, ylimits, disp_name) {

  print(c("Plotting ",column))
  g <- ggplot(data, aes_string(x=row, y=column))+
        geom_line(aes_string(x=row, y=column))+
        expand_limits(y = ylimits) +
        xlab("Time (s)")+
        scale_y_continuous(name=disp_name, breaks=seq(ylimits[1], ylimits[2], (ylimits[2]-ylimits[1])/1))

  if (!axis_element) {
      g <- g+ theme(axis.title.x =element_blank(),
                  axis.text.x  =element_blank(),
                  axis.ticks.x =element_blank())
  }
  return(g)
}

filter_and_decimate <- function(vector, dfactor) {
  filt_type <- "fir"
  filt_n <- 26
  offset <- vector[1]
  result = pmax(decimate(vector-offset,dfactor, n=filt_n, ftype=filt_type)+offset,0)
  return(result)
}


outputfilename <- "tracesin.pdf"
rawdata <- read.csv("../data/trace_in.csv", header=TRUE)
dfactor <- 120

columns <- c("Time","B","C","BHL","CHL")
columns_names <- c("Time (s)", "Solar (out)", "Solar (in+out) ","Detect(out)"," Detect(in)")

plotdata <- ''
time_start = min(rawdata[["Time"]])
print(time_start)

for (column in columns) {
  column_values <- filter_and_decimate(rawdata[,column],dfactor)
  if (plotdata != '') {
    plotdata[column] <- column_values
  } else {
    plotdata <- data.frame(column_values-time_start)
    #plotdata <- data.frame(column_values)
  }
}




colnames(plotdata) <- columns

#plots <- lapply(columns[-c(1)], plot_trace, data = plotdata, row="Time",axis_element=tail(columns,1));

ps_out <- plot_trace("B",plotdata,"Time",FALSE, c(2.5,2.8), "Solar\nOut (V)")
ps_in <- plot_trace("C",plotdata,"Time",FALSE, c(4.2,4.4), "Solar\nIn+Out (V)")
d_out <- plot_trace("BHL",plotdata,"Time", TRUE, c(0,2.1), "Detect\nOut")
d_in <- plot_trace("CHL",plotdata,"Time",FALSE, c(0,2.1),"Detect\nIn+Out")

plots <- list(ps_in, ps_out, d_in, d_out);



g <- arrangeGrob(grobs=plots, ncol=1, heights=c(1,1,0.6,1.0))

ggsave(outputfilename, width=4, height=4, pointsize=18, device=cairo_pdf,g);
