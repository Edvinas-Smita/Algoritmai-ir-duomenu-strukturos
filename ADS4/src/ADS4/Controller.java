package ADS4;

import javafx.fxml.FXML;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;

public class Controller
{
	@FXML
	private TextField fileNameTextBox, outputField;
	@FXML
	private ComboBox fromCombo, toCombo;
	
	private List<City> cities = null;
	private boolean canDoTheThing = true;
	
	@FXML
	public void initialize()
	{
		try
		{
			cities = Txt2Data.read("sample.txt");
			fromCombo.getItems().setAll(cities);
			toCombo.getItems().setAll(cities);
		}
		catch (IOException e)
		{
			canDoTheThing = false;
			e.printStackTrace();
		}
	}
	@FXML
	public void fileNameChanged()
	{
		try
		{
			cities = Txt2Data.read(fileNameTextBox.getText());
			fromCombo.getItems().clear();
			toCombo.getItems().clear();
			fromCombo.getItems().setAll(cities);
			toCombo.getItems().setAll(cities);
			canDoTheThing = true;
			fileNameTextBox.setStyle("-fx-background-color: rgb(255, 255, 255);");
		}
		catch (Exception e)
		{
			canDoTheThing = false;
			fileNameTextBox.setStyle("-fx-background-color: rgb(255, 0, 0);");
		}
	}
	
	@FXML
	public void doTheThing()
	{
		City.purge(cities);
		if (canDoTheThing)
		{
			outputField.setText(City.fly((City) fromCombo.getSelectionModel().getSelectedItem(), (City) toCombo.getSelectionModel().getSelectedItem()));
		}
		else
		{
			outputField.setText("Something went wrong...");
		}
	}
}
