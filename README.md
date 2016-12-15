# HFMacros
This folder contains files obtained by processing tree files. Tree files are located at TIFR



Step 1:
	Download the file containg histograms from TIFR.
Step 2: (Must: Step 1)
	In root:.x hist_fit.C("DownloadedFileName.root");
		This will produce a file named "fit_DownloadedFileName.root" and 4 or 5 pdf files(depending on the no. of cuts applied on Energy). Name of pdf files will
		be that of the folders inside "DownloadedFileName.root". It will fit pol1 through E2 vs E1 plots and pol0 through ratio vs E1 plots.
	Example:	.x hist_fit.C ("254833_E2E1Hists.root");
		O/P:    fit_254833_E2E1Hists.root E1E2Cut0Ieta.pdf E1E2Cut1Ieta.pdf E1E2Cut2Ieta.pdf E1E2Cut3Ieta.pdf E1E2Cut4Ieta.pdf
Sep 3: (Must: Step 1 and 2)
	In root:.x arrangePlots.C ("fit_DownloadedFileName.root","DirName");
		This will arrange 26 plots(ieta plots) in 4 canvases with +ve ieta on top pads and -ve ieta on battom pads. ieta= +/-41 are drawn on last canvas(canvas 		index 3). This can be done on E2 vs E1 plots or on ratio vs E1 plots.
	Example:	.x arrangePlots.C ("fit_254833_E2E1Hists.root","E1E2Cut3Ieta");
			.x arrangePlots.C ("fit_254833_E2E1Hists.root","RatiovsE1_ECut3Ieta");
		O/P:	4 Canvases and no new output file produced.

Overlay.C("iDirName")
	-This will overlay E2 vs E1 profile plots obtained for different runs.
	-Requirements: Step 1 and 2 for all files to be overlayed. (need to have fitted profile histograms)	
	-O/P: 8 canvases(1 empty) with 4 pads in each corresponding to 4 ieta
	     Overlayed.root  (this is empty)
	-Ex.: .x Overlay.C("E1E2Cut1Ieta");

plots.C(29)
	-Fit ratio plots(for each ieta) with asymmetric guassian. I/P argument is the starting point of ieta. It can be 29, 33, 37 or 41 only. If you give any
         other argument, it will take it as 29 and do the fitting for 29,30,31 and 32(plus and minus). File names to be given in the script itself. It can also overlay
	 2 fittings by uncommenting Overlay(etaask);
	-Requirements: Step 1. 
	-O/P: 2 Canvases(one is not useful) and plots.root. First canvas has 4X2 pads for 8 ieta. If you give ieta 33, then the canvas will have fitted plots for 
	     +/-(33,34,35,36). And this canvas is saved in plots.root. Prints parametrs related to fitting.
	-Ex: .x plots.C(33);

plots_asymgaus_fit.C
	-Fit ratio plots(for one ieta) with guassian and asymmetric guassian.
	-Ex:  .L plots_asymgaus_fit.C
	      plots(32);

RatioSummary.C("DownloadedFileName.root")
	-Get the mean and the error on mean from 1D plot of ratio(for each ieta) and plot these values as a function of ieta. You can have truncated mean instead of 
	 mean(uncomment appropriate lines and set 90% or 95% for truncated mean)
	-Requirements: Step 1. 
	- O/P: mRatiovsIeta_DownloadedFileName.root This will have mean(truncated or untruncated) vs ieta plots for different E1 E2 cuts.
	-Ex: .x RatioSummary.C("208307_E2E1Hists.root"); O/P: mRatiovsIeta_208307_E2E1Hists.root

mRatiovsIetaCompareRuns.C
	-This will create mean ratio vs ieta plot on a single canvas. This is done for a perticular E1 E2 cut which is decided given in the sript itself.This will
	 compare three different runs. The name of the files should be given in the script itself. 
	-Requirements: Step 1.
		       RatioSummary.C("DownloadedFileName.root")
	-O/P: 1 Canvas comapring different runs.
	-Ex: .x mRatiovsIetaCompareRuns.C; Assuming that you have done .x RatioSummary.C("DownloadedFileName.root") for three different runs and specified 
						   the valid files(mRatiovs_DownloadedFileName.root) in script.

RatioSummaryIphi.C("DownloadedFileName.root")
	-Get the mean and the error on mean from 1D plot of ratio(for each ieta and iphi) and plot these values as a function of iphi corresponding to each ieta.(For a
         given ieta you plot mean ratio as a function of iphi).
	-Requirements: Step 1. 
	- O/P: mRatiovsIphi_DownloadedFileName.root This will have mean vs iphi plots for each ieta corresponding to different cuts on E1 and E2.
	-Ex: .x RatioSummaryIphi.C("208307_E2E1Hists.root"); O/P:mRatiovsIphi_208307_E2E1Hists.root

ArrangeIeta.C("iDirName")
	-This will arrange mean ratio vs iphi plots for different ieta on 4 canvases(4X2 canvases). For ex, canvas 0 will have mean ratio vs iphi plots for 
	 +/-(29,30,31,32). This is done for a perticular E1 E2 cut which is decided by the "iDirName".This will compare three different runs. The name of the files
	 should be given in the script itself. 
	-Requirements: Step 1,
		       RatioSummaryIphi.C("DownloadedFileName.root")	
	-Ex: .x ArrangeIeta.C("E1E2Cut3Ietaiphi"); Assuming that you have done .x RatioSummaryIphi.C("DownloadedFileName.root") for three different runs and specified 
						   the valid files(mRatiovsIphi_DownloadedFileName.root) in script.



Ratio1DPlotsComapreRuns.C("iDirName")
	-Arrange 1D ratio histograms in 4 canvases according to value of ieta for different runs. File names must be listed in script iself along with number of files
	 and the colors for drwing these. One can compare n number of files.
	-Requirements: Step 1
	-O/P: 4 canvases comparing 1D ratio plots for different runs.
	-Ex: .x Ratio1DPlotsComapreRuns.C("E1E2Cut2Ratio");

EnergyPlotsComparison.C(int)
	-Get projection from 2D plots of E2 vs E1 and arrange these according to ieta. This will give 1D energy distributions in long(or short) for different runs. 
	 The I/P argument is for specifying the cut(Energy cut1 Energy cut2 etc).
	-Requirements: Step 1
	-O/P: 4 canvases comparing 1D energy in long(or short) plots for different runs.
	-Ex: .x EnergyPlotsComparison.C(2);








	
