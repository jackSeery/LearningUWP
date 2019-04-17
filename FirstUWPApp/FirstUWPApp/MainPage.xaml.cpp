//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace FirstUWPApp;

using namespace Platform;
using namespace Windows::Devices::Input;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();

	forceManipulationsToEnd = false;

	InitOptions();

	// Initialize the transforms that will be used to manipulate the shape
	InitManipulationTransforms();

	// Register for the various manipulation events that will occur on the shape
	manipulateMe->ManipulationStarted += ref new ManipulationStartedEventHandler(this, &MainPage::ManipulateMe_ManipulationStarted);
	manipulateMe->ManipulationDelta += ref new ManipulationDeltaEventHandler(this, &MainPage::ManipulateMe_ManipulationDelta);
	manipulateMe->ManipulationCompleted += ref new ManipulationCompletedEventHandler(this, &MainPage::ManipulateMe_ManipulationCompleted);
	manipulateMe->ManipulationInertiaStarting += ref new ManipulationInertiaStartingEventHandler(this, &MainPage::ManipulateMe_ManipulationInertiaStarting);

	// The ManipulationMode property dictates what manipulation events the element
	// will listen to.  This will set it to a limited subset of these events.
	manipulateMe->ManipulationMode =
		ManipulationModes::TranslateX |
		ManipulationModes::TranslateY |
		ManipulationModes::Rotate |
		ManipulationModes::TranslateInertia |
		ManipulationModes::RotateInertia;
}

void MainPage::InitManipulationTransforms()
{
	transforms = ref new TransformGroup();
	previousTransform = ref new MatrixTransform();
	previousTransform->Matrix = Matrix::Identity;

	deltaTransform = ref new CompositeTransform();

	transforms->Children->Append(previousTransform);
	transforms->Children->Append(deltaTransform);

	// Set the render transform on the rect
	manipulateMe->RenderTransform = transforms;
}

// When a manipulation begins, change the color of the object to reflect
// that a manipulation is in progress
void MainPage::ManipulateMe_ManipulationStarted(Platform::Object^ sender, ManipulationStartedRoutedEventArgs^ e)
{
	forceManipulationsToEnd = false;
	manipulateMe->Background = ref new SolidColorBrush(Windows::UI::Colors::DeepSkyBlue);
}

// Process the change resulting from a manipulation
void MainPage::ManipulateMe_ManipulationDelta(Platform::Object^ sender, ManipulationDeltaRoutedEventArgs^ e)
{
	// If the reset button has been pressed, mark the manipulation as completed
	if (forceManipulationsToEnd)
	{
		e->Complete();
		return;
	}

	previousTransform->Matrix = transforms->Value;

	// Get center point for rotation
	Point center = previousTransform->TransformPoint(Point(e->Position.X, e->Position.Y));
	deltaTransform->CenterX = center.X;
	deltaTransform->CenterY = center.Y;

	// Look at the Delta property of the ManipulationDeltaRoutedEventArgs to retrieve
	// the rotation, scale, X, and Y changes
	deltaTransform->Rotation = e->Delta.Rotation;
	deltaTransform->TranslateX = e->Delta.Translation.X;
	deltaTransform->TranslateY = e->Delta.Translation.Y;
}

// When a manipulation that's a result of inertia begins, change the color of the
// the object to reflect that inertia has taken over
void MainPage::ManipulateMe_ManipulationInertiaStarting(Platform::Object^ sender, ManipulationInertiaStartingRoutedEventArgs^ e)
{
	manipulateMe->Background = ref new SolidColorBrush(Windows::UI::Colors::RoyalBlue);
}

// When a manipulation has finished, reset the color of the object
void MainPage::ManipulateMe_ManipulationCompleted(Platform::Object^ sender, ManipulationCompletedRoutedEventArgs^ e)
{
	manipulateMe->Background = ref new SolidColorBrush(Windows::UI::Colors::LightGray);
}

void MainPage::movementAxis_Changed(Platform::Object^ sender, SelectionChangedEventArgs^ e)
{
	// Set the object to listen to both X and Y translation events
	auto mode = manipulateMe->ManipulationMode;
	auto update = ManipulationModes::TranslateX | ManipulationModes::TranslateY;
	manipulateMe->ManipulationMode = mode | update;

	ComboBox^ cb = dynamic_cast<ComboBox^>(sender);
	ComboBoxItem^ selectedItem = dynamic_cast<ComboBoxItem^>((cb)->SelectedItem);

	auto selection = selectedItem->Content->ToString();

	if (selection == L"X only")
	{
		// Set the object to not listen for translations on the Y axis
		auto mode = manipulateMe->ManipulationMode;
		manipulateMe->ManipulationMode = mode ^ ManipulationModes::TranslateY;
	}
	else if (selection == L"Y only")
	{
		auto mode = manipulateMe->ManipulationMode;
		manipulateMe->ManipulationMode = mode ^ ManipulationModes::TranslateX;

	}
}

void MainPage::InertiaSwitch_Toggled(Platform::Object^ sender, RoutedEventArgs^ e)
{
	// Flip the current TranslateInertia and RotateInertia values in response to the
	// InertiaSwitch being toggled
	if (manipulateMe != nullptr)
	{
		auto mode = manipulateMe->ManipulationMode;
		auto update = ManipulationModes::TranslateInertia | ManipulationModes::RotateInertia;
		manipulateMe->ManipulationMode = mode ^ update;
	}
}

//
// More UI code below
//
void MainPage::InitOptions()
{
	movementAxis->SelectedIndex = 0;
	inertiaSwitch->IsOn = true;
}

void MainPage::resetButton_Pressed(Platform::Object^ sender, RoutedEventArgs^ e)
{
	forceManipulationsToEnd = true;
	manipulateMe->RenderTransform = nullptr;
	movementAxis->SelectedIndex = 0;
	InitOptions();
	InitManipulationTransforms();
}
