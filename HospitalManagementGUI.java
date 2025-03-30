import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.*;
import java.sql.*;

public class HospitalManagementGUI extends JFrame {
    // Database connection
    private Connection conn;
    private String dbPath = "jdbc:sqlite:db/hospital.db";

    // UI Components
    private JTabbedPane tabbedPane;
    private JPanel hospitalPanel, patientPanel, doctorPanel, nursePanel, pharmacyPanel;
    
    // Tables
    private JTable hospitalTable, patientTable, doctorTable, nurseTable, pharmacyTable;
    private DefaultTableModel hospitalModel, patientModel, doctorModel, nurseModel, pharmacyModel;

    public HospitalManagementGUI() {
        // Set up the frame
        super("Hospital Management System");
        setSize(800, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Connect to the database
        connectToDatabase();

        // Initialize the UI
        initUI();

        // Load initial data
        loadAllData();
    }

    private void connectToDatabase() {
        try {
            // Load SQLite JDBC driver
            Class.forName("org.sqlite.JDBC");
            
            // Connect to the database
            conn = DriverManager.getConnection(dbPath);
            System.out.println("Connected to the database successfully");
        } catch (ClassNotFoundException | SQLException e) {
            JOptionPane.showMessageDialog(this, "Database Connection Error: " + e.getMessage(), 
                                         "Error", JOptionPane.ERROR_MESSAGE);
            e.printStackTrace();
            System.exit(1);
        }
    }

    private void initUI() {
        // Create tabbed pane
        tabbedPane = new JTabbedPane();
        
        // Initialize all panels
        initHospitalPanel();
        initPatientPanel();
        initDoctorPanel();
        initNursePanel();
        initPharmacyPanel();
        
        // Add panels to tabbed pane
        tabbedPane.addTab("Hospitals", hospitalPanel);
        tabbedPane.addTab("Patients", patientPanel);
        tabbedPane.addTab("Doctors", doctorPanel);
        tabbedPane.addTab("Nurses", nursePanel);
        tabbedPane.addTab("Pharmacies", pharmacyPanel);
        
        // Add tabbed pane to frame
        add(tabbedPane);
    }

    private void initHospitalPanel() {
        hospitalPanel = new JPanel(new BorderLayout());
        
        // Create table model
        hospitalModel = new DefaultTableModel();
        hospitalModel.addColumn("ID");
        hospitalModel.addColumn("Name");
        
        // Create table
        hospitalTable = new JTable(hospitalModel);
        JScrollPane scrollPane = new JScrollPane(hospitalTable);
        
        // Create button panel
        JPanel buttonPanel = new JPanel();
        JButton addButton = new JButton("Add Hospital");
        JButton refreshButton = new JButton("Refresh");
        
        // Add action listeners
        addButton.addActionListener(e -> addHospital());
        refreshButton.addActionListener(e -> loadHospitals());
        
        // Add buttons to panel
        buttonPanel.add(addButton);
        buttonPanel.add(refreshButton);
        
        // Add components to hospital panel
        hospitalPanel.add(scrollPane, BorderLayout.CENTER);
        hospitalPanel.add(buttonPanel, BorderLayout.SOUTH);
    }

    private void initPatientPanel() {
        patientPanel = new JPanel(new BorderLayout());
        
        // Create table model
        patientModel = new DefaultTableModel();
        patientModel.addColumn("ID");
        patientModel.addColumn("Name");
        patientModel.addColumn("Disease");
        patientModel.addColumn("Bill");
        patientModel.addColumn("Days");
        patientModel.addColumn("Status");
        
        // Create table
        patientTable = new JTable(patientModel);
        JScrollPane scrollPane = new JScrollPane(patientTable);
        
        // Create button panel
        JPanel buttonPanel = new JPanel();
        JButton addButton = new JButton("Admit Patient");
        JButton dischargeButton = new JButton("Discharge Patient");
        JButton refreshButton = new JButton("Refresh");
        
        // Add action listeners
        addButton.addActionListener(e -> admitPatient());
        dischargeButton.addActionListener(e -> dischargePatient());
        refreshButton.addActionListener(e -> loadPatients());
        
        // Add buttons to panel
        buttonPanel.add(addButton);
        buttonPanel.add(dischargeButton);
        buttonPanel.add(refreshButton);
        
        // Add components to patient panel
        patientPanel.add(scrollPane, BorderLayout.CENTER);
        patientPanel.add(buttonPanel, BorderLayout.SOUTH);
    }

    private void initDoctorPanel() {
        doctorPanel = new JPanel(new BorderLayout());
        
        // Create table model
        doctorModel = new DefaultTableModel();
        doctorModel.addColumn("ID");
        doctorModel.addColumn("Name");
        doctorModel.addColumn("Role");
        doctorModel.addColumn("Patients");
        
        // Create table
        doctorTable = new JTable(doctorModel);
        JScrollPane scrollPane = new JScrollPane(doctorTable);
        
        // Create button panel
        JPanel buttonPanel = new JPanel();
        JButton addButton = new JButton("Add Doctor");
        JButton assignButton = new JButton("Assign to Hospital");
        JButton assignPatientButton = new JButton("Assign Patient");
        JButton viewPatientsButton = new JButton("View Patients");
        JButton refreshButton = new JButton("Refresh");
        
        // Add action listeners
        addButton.addActionListener(e -> addDoctor());
        assignButton.addActionListener(e -> assignDoctor());
        assignPatientButton.addActionListener(e -> assignDoctorToPatient());
        viewPatientsButton.addActionListener(e -> viewDoctorPatients());
        refreshButton.addActionListener(e -> loadDoctors());
        
        // Add buttons to panel
        buttonPanel.add(addButton);
        buttonPanel.add(assignButton);
        buttonPanel.add(assignPatientButton);
        buttonPanel.add(viewPatientsButton);
        buttonPanel.add(refreshButton);
        
        // Add components to doctor panel
        doctorPanel.add(scrollPane, BorderLayout.CENTER);
        doctorPanel.add(buttonPanel, BorderLayout.SOUTH);
    }

    private void initNursePanel() {
        nursePanel = new JPanel(new BorderLayout());
        
        // Create table model
        nurseModel = new DefaultTableModel();
        nurseModel.addColumn("ID");
        nurseModel.addColumn("Name");
        
        // Create table
        nurseTable = new JTable(nurseModel);
        JScrollPane scrollPane = new JScrollPane(nurseTable);
        
        // Create button panel
        JPanel buttonPanel = new JPanel();
        JButton addButton = new JButton("Add Nurse");
        JButton assignButton = new JButton("Assign to Hospital");
        JButton refreshButton = new JButton("Refresh");
        
        // Add action listeners
        addButton.addActionListener(e -> addNurse());
        assignButton.addActionListener(e -> assignNurse());
        refreshButton.addActionListener(e -> loadNurses());
        
        // Add buttons to panel
        buttonPanel.add(addButton);
        buttonPanel.add(assignButton);
        buttonPanel.add(refreshButton);
        
        // Add components to nurse panel
        nursePanel.add(scrollPane, BorderLayout.CENTER);
        nursePanel.add(buttonPanel, BorderLayout.SOUTH);
    }

    private void initPharmacyPanel() {
        pharmacyPanel = new JPanel(new BorderLayout());
        
        // Create table model
        pharmacyModel = new DefaultTableModel();
        pharmacyModel.addColumn("ID");
        pharmacyModel.addColumn("Name");
        
        // Create table
        pharmacyTable = new JTable(pharmacyModel);
        JScrollPane scrollPane = new JScrollPane(pharmacyTable);
        
        // Create button panel
        JPanel buttonPanel = new JPanel();
        JButton addButton = new JButton("Add Pharmacy");
        JButton deliverButton = new JButton("Deliver Medicine");
        JButton viewBillButton = new JButton("View Bills");
        JButton refreshButton = new JButton("Refresh");
        
        // Add action listeners
        addButton.addActionListener(e -> addPharmacy());
        deliverButton.addActionListener(e -> deliverMedicine());
        viewBillButton.addActionListener(e -> viewPharmacyBills());
        refreshButton.addActionListener(e -> loadPharmacies());
        
        // Add buttons to panel
        buttonPanel.add(addButton);
        buttonPanel.add(deliverButton);
        buttonPanel.add(viewBillButton);
        buttonPanel.add(refreshButton);
        
        // Add components to pharmacy panel
        pharmacyPanel.add(scrollPane, BorderLayout.CENTER);
        pharmacyPanel.add(buttonPanel, BorderLayout.SOUTH);
    }

    // Load all data from database
    private void loadAllData() {
        loadHospitals();
        loadPatients();
        loadDoctors();
        loadNurses();
        loadPharmacies();
    }

    // Hospital methods
    private void loadHospitals() {
        try {
            // Clear existing data
            hospitalModel.setRowCount(0);
            
            // Prepare and execute query
            String query = "SELECT id, name FROM Hospital";
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            
            // Add data to table model
            while (rs.next()) {
                Object[] row = {
                    rs.getInt("id"),
                    rs.getString("name")
                };
                hospitalModel.addRow(row);
            }
            
            rs.close();
            stmt.close();
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Error loading hospitals: " + e.getMessage(), 
                                         "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void addHospital() {
        String name = JOptionPane.showInputDialog(this, "Enter hospital name:");
        if (name != null && !name.trim().isEmpty()) {
            try {
                String query = "INSERT INTO Hospital (name) VALUES (?)";
                PreparedStatement pstmt = conn.prepareStatement(query);
                pstmt.setString(1, name.trim());
                pstmt.executeUpdate();
                pstmt.close();
                
                JOptionPane.showMessageDialog(this, "Hospital added successfully!");
                loadHospitals();
            } catch (SQLException e) {
                JOptionPane.showMessageDialog(this, "Error adding hospital: " + e.getMessage(), 
                                             "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    // Patient methods
    private void loadPatients() {
        try {
            // Clear existing data
            patientModel.setRowCount(0);
            
            // Prepare and execute query
            String query = "SELECT id, name, disease, bill, daysInHospital, status FROM Patient";
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            
            // Add data to table model
            while (rs.next()) {
                String status = rs.getInt("status") == 1 ? "In Hospital" : "Discharged";
                Object[] row = {
                    rs.getInt("id"),
                    rs.getString("name"),
                    rs.getString("disease"),
                    rs.getInt("bill"),
                    rs.getInt("daysInHospital"),
                    status
                };
                patientModel.addRow(row);
            }
            
            rs.close();
            stmt.close();
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Error loading patients: " + e.getMessage(), 
                                         "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void admitPatient() {
        // Get list of hospitals for dropdown
        Object[] hospitals = getHospitalList();
        if (hospitals.length == 0) {
            JOptionPane.showMessageDialog(this, "No hospitals available. Please add a hospital first.");
            return;
        }
        
        // Create form components
        JComboBox<Object> hospitalCombo = new JComboBox<>(hospitals);
        JTextField nameField = new JTextField();
        JTextField diseaseField = new JTextField();
        JTextField costField = new JTextField();
        
        // Create panel for form
        JPanel panel = new JPanel(new GridLayout(0, 2));
        panel.add(new JLabel("Hospital:"));
        panel.add(hospitalCombo);
        panel.add(new JLabel("Patient Name:"));
        panel.add(nameField);
        panel.add(new JLabel("Disease:"));
        panel.add(diseaseField);
        panel.add(new JLabel("Cost per Day:"));
        panel.add(costField);
        
        // Show dialog
        int result = JOptionPane.showConfirmDialog(this, panel, "Admit Patient", 
                                                 JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
        
        if (result == JOptionPane.OK_OPTION) {
            String name = nameField.getText().trim();
            String disease = diseaseField.getText().trim();
            String costStr = costField.getText().trim();
            
            if (name.isEmpty() || disease.isEmpty() || costStr.isEmpty()) {
                JOptionPane.showMessageDialog(this, "All fields are required.");
                return;
            }
            
            try {
                int cost = Integer.parseInt(costStr);
                String selectedHospital = hospitalCombo.getSelectedItem().toString();
                int hospitalId = Integer.parseInt(selectedHospital.split(":")[0].trim());
                
                String query = "INSERT INTO Patient (name, disease, bill, id) VALUES (?, ?, ?, ?)";
                PreparedStatement pstmt = conn.prepareStatement(query);
                pstmt.setString(1, name);
                pstmt.setString(2, disease);
                pstmt.setInt(3, cost);
                pstmt.setInt(4, hospitalId);
                pstmt.executeUpdate();
                pstmt.close();
                
                JOptionPane.showMessageDialog(this, "Patient admitted successfully!");
                loadPatients();
            } catch (NumberFormatException e) {
                JOptionPane.showMessageDialog(this, "Cost must be a number.");
            } catch (SQLException e) {
                JOptionPane.showMessageDialog(this, "Error admitting patient: " + e.getMessage(), 
                                             "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    private void dischargePatient() {
        // Get selected patient
        int selectedRow = patientTable.getSelectedRow();
        if (selectedRow == -1) {
            JOptionPane.showMessageDialog(this, "Please select a patient to discharge.");
            return;
        }
        
        int patientId = (int)patientModel.getValueAt(selectedRow, 0);
        String status = (String)patientModel.getValueAt(selectedRow, 5);
        
        if (!status.equals("In Hospital")) {
            JOptionPane.showMessageDialog(this, "This patient is already discharged.");
            return;
        }
        
        try {
            String query = "UPDATE Patient SET status = 0 WHERE id = ?";
            PreparedStatement pstmt = conn.prepareStatement(query);
            pstmt.setInt(1, patientId);
            pstmt.executeUpdate();
            pstmt.close();
            
            JOptionPane.showMessageDialog(this, "Patient discharged successfully!");
            loadPatients();
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Error discharging patient: " + e.getMessage(), 
                                         "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    // Doctor methods
    private void loadDoctors() {
        try {
            // Clear existing data
            doctorModel.setRowCount(0);
            
            // Prepare and execute query
            String query = "SELECT d.id, d.name, d.role, COUNT(dp.patient_id) as patient_count " +
                         "FROM Doctor d " +
                         "LEFT JOIN Doctor_Patient dp ON d.id = dp.doctor_id " +
                         "GROUP BY d.id";
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            
            // Add data to table model
            while (rs.next()) {
                Object[] row = {
                    rs.getInt("id"),
                    rs.getString("name"),
                    rs.getString("role"),
                    rs.getInt("patient_count")
                };
                doctorModel.addRow(row);
            }
            
            rs.close();
            stmt.close();
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Error loading doctors: " + e.getMessage(), 
                                         "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void addDoctor() {
        // Create form components
        JTextField nameField = new JTextField();
        JTextField roleField = new JTextField();
        
        // Create panel for form
        JPanel panel = new JPanel(new GridLayout(0, 2));
        panel.add(new JLabel("Doctor Name:"));
        panel.add(nameField);
        panel.add(new JLabel("Role:"));
        panel.add(roleField);
        
        // Show dialog
        int result = JOptionPane.showConfirmDialog(this, panel, "Add Doctor", 
                                                 JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
        
        if (result == JOptionPane.OK_OPTION) {
            String name = nameField.getText().trim();
            String role = roleField.getText().trim();
            
            if (name.isEmpty() || role.isEmpty()) {
                JOptionPane.showMessageDialog(this, "All fields are required.");
                return;
            }
            
            try {
                String query = "INSERT INTO Doctor (name, role) VALUES (?, ?)";
                PreparedStatement pstmt = conn.prepareStatement(query);
                pstmt.setString(1, name);
                pstmt.setString(2, role);
                pstmt.executeUpdate();
                pstmt.close();
                
                JOptionPane.showMessageDialog(this, "Doctor added successfully!");
                loadDoctors();
            } catch (SQLException e) {
                JOptionPane.showMessageDialog(this, "Error adding doctor: " + e.getMessage(), 
                                             "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    private void assignDoctor() {
        // Implementation of assigning doctor to hospital
        // This would need additional database tables to track the relationship
        JOptionPane.showMessageDialog(this, "Assign Doctor functionality not fully implemented yet.");
    }

    private void assignDoctorToPatient() {
        // Get selected doctor
        int selectedRow = doctorTable.getSelectedRow();
        if (selectedRow == -1) {
            JOptionPane.showMessageDialog(this, "Please select a doctor first.");
            return;
        }
        
        int doctorId = (int)doctorModel.getValueAt(selectedRow, 0);
        
        // Get list of patients for dropdown
        Object[] patients = getPatientList();
        if (patients.length == 0) {
            JOptionPane.showMessageDialog(this, "No patients available.");
            return;
        }
        
        // Create form components
        JComboBox<Object> patientCombo = new JComboBox<>(patients);
        JCheckBox primaryCheckBox = new JCheckBox("Primary Doctor");
        
        // Create panel for form
        JPanel panel = new JPanel(new GridLayout(0, 2));
        panel.add(new JLabel("Patient:"));
        panel.add(patientCombo);
        panel.add(new JLabel(""));
        panel.add(primaryCheckBox);
        
        // Show dialog
        int result = JOptionPane.showConfirmDialog(this, panel, "Assign Patient to Doctor", 
                                                 JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
        
        if (result == JOptionPane.OK_OPTION) {
            String selectedPatient = patientCombo.getSelectedItem().toString();
            int patientId = Integer.parseInt(selectedPatient.split(":")[0].trim());
            boolean isPrimary = primaryCheckBox.isSelected();
            
            try {
                String query = "INSERT INTO Doctor_Patient (doctor_id, patient_id, is_primary) VALUES (?, ?, ?)";
                PreparedStatement pstmt = conn.prepareStatement(query);
                pstmt.setInt(1, doctorId);
                pstmt.setInt(2, patientId);
                pstmt.setInt(3, isPrimary ? 1 : 0);
                pstmt.executeUpdate();
                pstmt.close();
                
                JOptionPane.showMessageDialog(this, "Patient assigned to doctor successfully!");
                loadDoctors();
            } catch (SQLException e) {
                JOptionPane.showMessageDialog(this, "Error assigning patient: " + e.getMessage(), 
                                             "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    private void viewDoctorPatients() {
        // Get selected doctor
        int selectedRow = doctorTable.getSelectedRow();
        if (selectedRow == -1) {
            JOptionPane.showMessageDialog(this, "Please select a doctor first.");
            return;
        }
        
        int doctorId = (int)doctorModel.getValueAt(selectedRow, 0);
        String doctorName = (String)doctorModel.getValueAt(selectedRow, 1);
        
        try {
            // Create a new dialog to show patients
            JDialog dialog = new JDialog(this, "Patients of " + doctorName, true);
            dialog.setSize(400, 300);
            dialog.setLocationRelativeTo(this);
            
            // Create table model for patients
            DefaultTableModel patientModel = new DefaultTableModel();
            patientModel.addColumn("ID");
            patientModel.addColumn("Name");
            patientModel.addColumn("Disease");
            patientModel.addColumn("Primary");
            
            // Create and populate table
            JTable patientTable = new JTable(patientModel);
            JScrollPane scrollPane = new JScrollPane(patientTable);
            
            // Query to get patients
            String query = "SELECT p.id, p.name, p.disease, dp.is_primary " +
                         "FROM Patient p " +
                         "JOIN Doctor_Patient dp ON p.id = dp.patient_id " +
                         "WHERE dp.doctor_id = ?";
            PreparedStatement pstmt = conn.prepareStatement(query);
            pstmt.setInt(1, doctorId);
            ResultSet rs = pstmt.executeQuery();
            
            while (rs.next()) {
                Object[] row = {
                    rs.getInt("id"),
                    rs.getString("name"),
                    rs.getString("disease"),
                    rs.getInt("is_primary") == 1 ? "Yes" : "No"
                };
                patientModel.addRow(row);
            }
            
            // Add close button
            JButton closeButton = new JButton("Close");
            closeButton.addActionListener(e -> dialog.dispose());
            
            // Add components to dialog
            dialog.add(scrollPane, BorderLayout.CENTER);
            dialog.add(closeButton, BorderLayout.SOUTH);
            
            dialog.setVisible(true);
            
            rs.close();
            pstmt.close();
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Error loading patients: " + e.getMessage(), 
                                         "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private Object[] getPatientList() {
        try {
            String query = "SELECT id, name FROM Patient";
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            
            java.util.List<String> patients = new java.util.ArrayList<>();
            while (rs.next()) {
                patients.add(rs.getInt("id") + ": " + rs.getString("name"));
            }
            
            rs.close();
            stmt.close();
            
            return patients.toArray();
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Error loading patients: " + e.getMessage(), 
                                         "Error", JOptionPane.ERROR_MESSAGE);
            return new Object[0];
        }
    }

    // Nurse methods
    private void loadNurses() {
        try {
            // Clear existing data
            nurseModel.setRowCount(0);
            
            // Prepare and execute query
            String query = "SELECT id, name FROM Nurse";
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            
            // Add data to table model
            while (rs.next()) {
                Object[] row = {
                    rs.getInt("id"),
                    rs.getString("name")
                };
                nurseModel.addRow(row);
            }
            
            rs.close();
            stmt.close();
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Error loading nurses: " + e.getMessage(), 
                                         "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void addNurse() {
        String name = JOptionPane.showInputDialog(this, "Enter nurse name:");
        if (name != null && !name.trim().isEmpty()) {
            try {
                String query = "INSERT INTO Nurse (name) VALUES (?)";
                PreparedStatement pstmt = conn.prepareStatement(query);
                pstmt.setString(1, name.trim());
                pstmt.executeUpdate();
                pstmt.close();
                
                JOptionPane.showMessageDialog(this, "Nurse added successfully!");
                loadNurses();
            } catch (SQLException e) {
                JOptionPane.showMessageDialog(this, "Error adding nurse: " + e.getMessage(), 
                                             "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    private void assignNurse() {
        // Implementation of assigning nurse to hospital
        // This would need additional database tables to track the relationship
        JOptionPane.showMessageDialog(this, "Assign Nurse functionality not fully implemented yet.");
    }

    // Pharmacy methods
    private void loadPharmacies() {
        try {
            // Clear existing data
            pharmacyModel.setRowCount(0);
            
            // Prepare and execute query
            String query = "SELECT id, name FROM Pharmacy";
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            
            // Add data to table model
            while (rs.next()) {
                Object[] row = {
                    rs.getInt("id"),
                    rs.getString("name")
                };
                pharmacyModel.addRow(row);
            }
            
            rs.close();
            stmt.close();
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Error loading pharmacies: " + e.getMessage(), 
                                         "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void addPharmacy() {
        // Create form components
        JTextField nameField = new JTextField();
        JTextField addressField = new JTextField();
        JTextField contactField = new JTextField();
        
        // Create panel for form
        JPanel panel = new JPanel(new GridLayout(0, 2));
        panel.add(new JLabel("Pharmacy Name:"));
        panel.add(nameField);
        panel.add(new JLabel("Address (optional):"));
        panel.add(addressField);
        panel.add(new JLabel("Contact (optional):"));
        panel.add(contactField);
        
        // Show dialog
        int result = JOptionPane.showConfirmDialog(this, panel, "Add Pharmacy", 
                                                 JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
        
        if (result == JOptionPane.OK_OPTION) {
            String name = nameField.getText().trim();
            
            if (name.isEmpty()) {
                JOptionPane.showMessageDialog(this, "Pharmacy name is required.");
                return;
            }
            
            try {
                String query = "INSERT INTO Pharmacy (name) VALUES (?)";
                PreparedStatement pstmt = conn.prepareStatement(query);
                pstmt.setString(1, name);
                pstmt.executeUpdate();
                pstmt.close();
                
                JOptionPane.showMessageDialog(this, "Pharmacy added successfully!");
                loadPharmacies();
            } catch (SQLException e) {
                JOptionPane.showMessageDialog(this, "Error adding pharmacy: " + e.getMessage(), 
                                             "Error", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    private void deliverMedicine() {
        // Get list of hospitals and pharmacies for dropdown
        Object[] hospitals = getHospitalList();
        Object[] pharmacies = getPharmacyList();
        
        if (hospitals.length == 0 || pharmacies.length == 0) {
            JOptionPane.showMessageDialog(this, "Both hospitals and pharmacies are needed for medicine delivery.");
            return;
        }
        
        // Create form components
        JComboBox<Object> pharmacyCombo = new JComboBox<>(pharmacies);
        JComboBox<Object> hospitalCombo = new JComboBox<>(hospitals);
        JTextField medicineField = new JTextField();
        JTextField costField = new JTextField();
        
        // Create panel for form
        JPanel panel = new JPanel(new GridLayout(0, 2));
        panel.add(new JLabel("Pharmacy:"));
        panel.add(pharmacyCombo);
        panel.add(new JLabel("Hospital:"));
        panel.add(hospitalCombo);
        panel.add(new JLabel("Medicine:"));
        panel.add(medicineField);
        panel.add(new JLabel("Cost:"));
        panel.add(costField);
        
        // Show dialog
        int result = JOptionPane.showConfirmDialog(this, panel, "Deliver Medicine", 
                                                 JOptionPane.OK_CANCEL_OPTION, JOptionPane.PLAIN_MESSAGE);
        
        if (result == JOptionPane.OK_OPTION) {
            String medicine = medicineField.getText().trim();
            String costStr = costField.getText().trim();
            
            if (medicine.isEmpty() || costStr.isEmpty()) {
                JOptionPane.showMessageDialog(this, "All fields are required.");
                return;
            }
            
            try {
                double cost = Double.parseDouble(costStr);
                String selectedPharmacy = pharmacyCombo.getSelectedItem().toString();
                String selectedHospital = hospitalCombo.getSelectedItem().toString();
                
                int pharmacyId = Integer.parseInt(selectedPharmacy.split(":")[0].trim());
                int hospitalId = Integer.parseInt(selectedHospital.split(":")[0].trim());
                
                // In a real application, we would record this transaction in a database table
                JOptionPane.showMessageDialog(this, 
                    "Medicine '" + medicine + "' delivered from Pharmacy #" + pharmacyId + 
                    " to Hospital #" + hospitalId + " for $" + cost);
            } catch (NumberFormatException e) {
                JOptionPane.showMessageDialog(this, "Cost must be a number.");
            }
        }
    }

    private void viewPharmacyBills() {
        JOptionPane.showMessageDialog(this, "Pharmacy billing functionality not fully implemented yet.");
    }

    // Helper methods
    private Object[] getHospitalList() {
        try {
            // Query hospitals
            String query = "SELECT id, name FROM Hospital";
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            
            // Add to list
            java.util.List<String> hospitals = new java.util.ArrayList<>();
            while (rs.next()) {
                hospitals.add(rs.getInt("id") + ": " + rs.getString("name"));
            }
            
            rs.close();
            stmt.close();
            
            return hospitals.toArray();
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Error getting hospital list: " + e.getMessage(), 
                                         "Error", JOptionPane.ERROR_MESSAGE);
            return new Object[0];
        }
    }

    private Object[] getPharmacyList() {
        try {
            // Query pharmacies
            String query = "SELECT id, name FROM Pharmacy";
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(query);
            
            // Add to list
            java.util.List<String> pharmacies = new java.util.ArrayList<>();
            while (rs.next()) {
                pharmacies.add(rs.getInt("id") + ": " + rs.getString("name"));
            }
            
            rs.close();
            stmt.close();
            
            return pharmacies.toArray();
        } catch (SQLException e) {
            JOptionPane.showMessageDialog(this, "Error getting pharmacy list: " + e.getMessage(), 
                                         "Error", JOptionPane.ERROR_MESSAGE);
            return new Object[0];
        }
    }

    // Main method
    public static void main(String[] args) {
        // Set look and feel to system default
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        // Run GUI on event dispatch thread
        SwingUtilities.invokeLater(() -> {
            HospitalManagementGUI gui = new HospitalManagementGUI();
            gui.setVisible(true);
        });
    }
} 