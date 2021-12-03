//
//  UserInfoVC.swift
//  FallFix App
//
//  Created by Arya Tschand on 11/1/21.
//

import UIKit

class UserInfoVC: UIViewController {
    
    
    @IBOutlet weak var GenderPick: UISegmentedControl!
    
    
    @IBOutlet weak var AgeField: UITextField!
    
    var genderVar: Bool = false
    
    @IBAction func ConnectBtn(_ sender: Any) {
        
        if (GenderPick.selectedSegmentIndex == 1) {
            genderVar = true
        } else {
            genderVar = false
        }
        getDelete()
        
        
    }
    
    func getLeader(gender: Bool, age:Int) {
        printMessagesForUser(gender: gender, age: age) {
                (returnval, error) in
                if (returnval)!
                {
                    DispatchQueue.main.async {
//put stuff to do after here
                        
                    }
                } else {
                    print(error)
                }
            }
            DispatchQueue.main.async { // Correct
            }
        }
    
    func getDelete() {
        printMessagesForDelete() {
                (returnval, error) in
                if (returnval)!
                {
                    DispatchQueue.main.async {
//put stuff to do after here
                        self.getLeader(gender: self.genderVar, age: Int(self.AgeField.text!)!)
                    }
                } else {
                    print(error)
                }
            }
            DispatchQueue.main.async { // Correct
            }
        }
    
    func printMessagesForDelete(CompletionHandler: @escaping (Bool?, Error?) -> Void){
        do {
            let myurl = NSURL(string: "http://172.28.132.254:5000/delete/arya125")
            let myrequest = NSMutableURLRequest(url: myurl as! URL)
            myrequest.httpMethod = "Get"
            
            let mytask = URLSession.shared.dataTask(with: myrequest as URLRequest){ data, response, error in
                    CompletionHandler(true,nil)
                
            }
            mytask.resume()
            
        } catch {
            
            print(error)
        }
    }
    
    
        
    func printMessagesForUser(gender: Bool, age:Int, CompletionHandler: @escaping (Bool?, Error?) -> Void){
        do {
            
            let url = NSURL(string: "http://172.28.132.254:5000/setuser/arya125/" + String(gender) + "/" + String(age))!
            let request = NSMutableURLRequest(url: url as URL)
            request.httpMethod = "Get"
            
            request.setValue("application/json; charset=utf-8", forHTTPHeaderField: "Content-Type")
            
            let task = URLSession.shared.dataTask(with: request as URLRequest){ data, response, error in
                if let returned = String(data: data!, encoding: .utf8) {
                    
                    CompletionHandler(true,nil)
                    
                    //self.Severity.text = "hello"
                } else {
                }
                
                //self.Severity.text = "test"
                
            }
            task.resume()
            
        } catch {
            
            print(error)
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.hideKeyboardWhenTappedAround()
        
        // Do any additional setup after loading the view.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}

extension UIViewController {
    func hideKeyboardWhenTappedAround() {
        let tap = UITapGestureRecognizer(target: self, action: #selector(UIViewController.dismissKeyboard))
        tap.cancelsTouchesInView = false
        view.addGestureRecognizer(tap)
    }
    
    @objc func dismissKeyboard() {
        view.endEditing(true)
    }
}
