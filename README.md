PhaseUnwrapping Module for 3D Slicer
====================================

This 3D Slicer CLI module unwraps phase images using the itkQualityGuidedPhaseUnwrappingImageFilter class developed by Vigneault et al. The detail of the algorithm and original source code of the class can be found at:

http://www.insight-journal.org/browse/publication/954

This CLI module rescales the input image to [0, 2*pi] range, before passing it to the phase unwrapping filter.


