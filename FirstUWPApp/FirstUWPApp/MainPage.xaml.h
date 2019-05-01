//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace FirstUWPApp
{
	ref class ManipulationInputProcessor sealed
	{
	public:
		ManipulationInputProcessor(Windows::UI::Input::GestureRecognizer^ gestureRecognizer, Windows::UI::Xaml::UIElement^ target, Windows::UI::Xaml::UIElement^ referenceFrame);
		void LockToXAxis();
		void LockToYAxis();
		void MoveOnXAndYAxes();
		void UseInertia(bool inertia);
		void Reset();

	private:
		void InitializeTransforms();
		Windows::UI::Input::GestureSettings GenerateDefaultSettings();
		void OnPointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);
		void OnPointerMoved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);
		void OnPointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);
		void OnPointerCanceled(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);
		void OnManipulationStarted(Windows::UI::Input::GestureRecognizer^, Windows::UI::Input::ManipulationStartedEventArgs^ e);
		void OnManipulationUpdated(Windows::UI::Input::GestureRecognizer^, Windows::UI::Input::ManipulationUpdatedEventArgs^ e);
		void OnManipulationInertiaStarting(Windows::UI::Input::GestureRecognizer^ r, Windows::UI::Input::ManipulationInertiaStartingEventArgs^ e);
		void OnManipulationCompleted(Windows::UI::Input::GestureRecognizer^, Windows::UI::Input::ManipulationCompletedEventArgs^ e);

		Windows::UI::Input::GestureRecognizer^ recognizer;
		Windows::UI::Xaml::UIElement^ element;
		Windows::UI::Xaml::UIElement^ reference;
		Windows::UI::Xaml::Media::TransformGroup^ cumulativeTransform;
		Windows::UI::Xaml::Media::MatrixTransform^ previousTransform;
		Windows::UI::Xaml::Media::CompositeTransform^ deltaTransform;
	};

	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
	private:
		void InitOptions();
		void movementAxis_Changed(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		void InertiaSwitch_Toggled(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void resetButton_Pressed(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		Windows::UI::Input::GestureRecognizer^ recognizer;
		ManipulationInputProcessor^ manipulationProcessor;
	};
}
