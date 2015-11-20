/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef __itkWrappedPhaseDifferencesBaseImageFilter_txx
#define __itkWrappedPhaseDifferencesBaseImageFilter_txx
 
namespace itk {

template< typename TInputImage, typename TOutputImage >
WrappedPhaseDifferencesBaseImageFilter< TInputImage, TOutputImage >
::WrappedPhaseDifferencesBaseImageFilter()
{}

template< typename TInputImage, typename TOutputImage >
typename TInputImage::Pointer
WrappedPhaseDifferencesBaseImageFilter< TInputImage, TOutputImage >
::DirectionalDerivative(unsigned int i)
{

  typename ShiftType::Pointer    m_Shift = ShiftType::New();
  typename ShiftType::OffsetType offset;
  typename SubtractType::Pointer m_Subtract = SubtractType::New();
  typename WrapType::Pointer     m_Wrap = WrapType::New();
  
  offset.Fill( 0 );
  offset[i] = -1;
  m_Shift->SetShift( offset );
  m_Shift->SetInput( this->GetInput() );

  m_Subtract->SetInput1( m_Shift->GetOutput() );
  m_Subtract->SetInput2( this->GetInput() );
  
  m_Wrap->SetInput( m_Subtract->GetOutput() );

  typename TInputImage::Pointer output = m_Wrap->GetOutput();
  m_Wrap->Update();
  output->Update();
  
  // Take care of the boundary conditions
  typename TInputImage::SizeType  size  = output->GetLargestPossibleRegion().GetSize();
  typename TInputImage::IndexType index = output->GetLargestPossibleRegion().GetIndex();
  index[i] += size[i] - 1;
  size[i] = 1;
  typename TInputImage::RegionType region( index, size );
  ItType outIt( output, region );
  outIt.GoToBegin();
  
  while (!outIt.IsAtEnd()) {
  
    outIt.Set( 0 );
    
    ++outIt;
  
  }
  
  return output;

}

template< typename TInputImage, typename TOutputImage >
typename WrappedPhaseDifferencesBaseImageFilter< TInputImage, TOutputImage >::TVectorPointer
WrappedPhaseDifferencesBaseImageFilter< TInputImage, TOutputImage >
::ComposeVector()
{

  typename ComposeType::Pointer m_Compose = ComposeType::New();

  for (unsigned int i = 0; i < TInputImage::ImageDimension; ++i) {

    m_Compose->SetInput( i, this->DirectionalDerivative( i ) );
	
  }
  
  m_Compose->Update();
  
  return m_Compose->GetOutput();

}

}// end namespace itk
 
#endif
