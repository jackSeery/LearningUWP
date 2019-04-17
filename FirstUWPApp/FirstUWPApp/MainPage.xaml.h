//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace FirstUWPApp
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
	private:
		void InitManipulationTransforms();
		void ManipulateMe_ManipulationStarted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ e);
		void ManipulateMe_ManipulationDelta(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ e);
		void ManipulateMe_ManipulationInertiaStarting(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ e);
		void ManipulateMe_ManipulationCompleted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs^ e);
		void movementAxis_Changed(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void InertiaSwitch_Toggled(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void InitOptions();
		void resetButton_Pressed(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		Windows::UI::Xaml::Media::TransformGroup^ transforms;
		Windows::UI::Xaml::Media::MatrixTransform^ previousTransform;
		Windows::UI::Xaml::Media::CompositeTransform^ deltaTransform;
		bool forceManipulationsToEnd;
	};
}
