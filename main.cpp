#include <cmath>
#include <iostream>
#include <stack>
#include "tokenizer.hpp"

int main(int argc, char** argv){
	if(argc < 2){
		std::cout << "j'ai besoin d'un contribution" << std::endl;
		return -1;
	}

	// need to tokenize and then construct the terms
	std::queue<Token> tokens = tokenize(argv[1]);

	std::stack<Token> outputStack;

	// proccesses infix math
	// if front token is a number: add to output stack
	// if operator: operate on the first 2 numbers and add result to output stack
	// (special for sin/cos/tan cause they only operator on one number)
	while(tokens.size() > 0){
		if(tokens.front().type == NUMBER || tokens.front().type == DECIMAL){
			outputStack.push(tokens.front());
		}
		else if(tokens.front().type >= ADD || tokens.front().type == WORD){
			float result = 0.f;
			Token token;
			token.type = NUMBER;
			token.raw = "calculation";
			if(tokens.front().type == ADD){
				result = outputStack.top().value;
				outputStack.pop();
				result += outputStack.top().value;
			}
			else if(tokens.front().type == SUB){
				result = outputStack.top().value;
				outputStack.pop();
				result -= outputStack.top().value;
			}
			else if(tokens.front().type == MUL){
				result = outputStack.top().value;
				outputStack.pop();
				result *= outputStack.top().value;
			}
			else if(tokens.front().type == DIV){
				result = outputStack.top().value;
				outputStack.pop();
				result /= outputStack.top().value;
			}
			else if(tokens.front().type == EXPONENT){
				int amount = outputStack.top().value;
				outputStack.pop();
				result = outputStack.top().value;
				float original = outputStack.top().value;
				while(amount > 1){
					result *= original;
					amount--;
				}
			}
			else if(tokens.front().type == WORD){
				if(tokens.front().raw == "sin"){
					result = std::sin(outputStack.top().value);
				}
				else if(tokens.front().raw == "cos"){
					result = std::cos(outputStack.top().value);
				}
				else if(tokens.front().raw == "tan"){
					result = std::tan(outputStack.top().value);
				}
			}
			outputStack.pop();
			token.value = result;
			outputStack.push(token);
		}
		tokens.pop();
	}

	std::cout << outputStack.top().value << std::endl;
	
	return 0;
}